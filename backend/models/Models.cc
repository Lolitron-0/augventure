#pragma GCC diagnostic push
// somehow std::stable_sort uses deprecated in C++17 std::get_temporary_buffer
// diagnostic push/pop didn't work in place because std::stable_sort is
// referened in <algorithm> (which is included by drogon), so I just left it
// here (probably I'm stupid)
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "Models.h"
#include "Suggestions.h"
#include <cstdint>
#include <drogon/orm/Criteria.h>
#include <drogon/orm/Exception.h>
#include <drogon/orm/Mapper.h>
#include <functional>
#include <json/value.h>
#include <list>
#include <memory>
#include <type_traits>

void getFullEventData(
    const Json::Value& eventJson,
    std::function<void(const Json::Value&)>&& successCallback,
    drogon::orm::DrogonDbExceptionCallback&& dbExceptionCallback)
{
    auto successCallbackPtr{
        std::make_shared<std::function<void(const Json::Value&)>>(
            successCallback)
    };
    Json::Value eventList{};
    eventList[0] = eventJson;
    expandEventList(
        std::move(eventList), [successCallbackPtr](auto&& result)
        { (*successCallbackPtr)(result[0]); },
        std::forward<decltype(dbExceptionCallback)>(dbExceptionCallback));
}

void expandEventList(
    const Json::Value& eventListJson,
    std::function<void(const Json::Value&)>&& successCallback,
    drogon::orm::DrogonDbExceptionCallback&& dbExceptionCallback)
{
    using namespace drogon_model::augventure_db;
    using namespace drogon::orm;

    auto resultJsonPtr{ std::make_shared<Json::Value>(
        std::move(eventListJson)) };
    auto successCallbackPtr{
        std::make_shared<std::function<void(const Json::Value&)>>(
            successCallback)
    };
    auto dbExceptionCallbackPtr{ std::make_shared<DrogonDbExceptionCallback>(
        dbExceptionCallback) };
    std::vector<PrimaryKeyType> eventIds{};
    for (int32_t i{ 0 }; i < resultJsonPtr->size(); i++)
    {
        eventIds.push_back((*resultJsonPtr)[i]["id"].as<PrimaryKeyType>());
    }

    auto dbClient{ drogon::app().getDbClient() };
    Mapper<Sprint> sprintMapper{ dbClient };
    sprintMapper.findBy(
        Criteria{ Sprints::Cols::_event_id, CompareOperator::In,
                  eventIds }, // eventIds can't be empty
        [successCallbackPtr, dbExceptionCallbackPtr, dbClient,
         resultJsonPtr](std::vector<Sprint> sprints)
        {
            if (sprints.empty()) // rare and fabricated
            {
                Json::Value tmp;
                for (auto& event : *resultJsonPtr)
                {
                    tmp = event;
                    event = Json::Value{};
                    event["event"] = std::move(tmp);
                }
                (*successCallbackPtr)(std::move(*resultJsonPtr));
            }

            Mapper<Posts> postsMapper{ dbClient };
            postsMapper.findBy(
                Criteria{ Posts::Cols::_sprint_id, CompareOperator::In,
                          std::invoke(
                              [&sprints]() // IIFE so won't
                              // invalidate
                              {
                                  std::vector<int> ids{};
                                  for (const auto& sprint : sprints)
                                      ids.push_back(sprint.getValueOfId());
                                  return ids;
                              }) },
                [sprintsList =
                     std::list<Sprint>(sprints.begin(), sprints.end()),
                 resultJsonPtr, successCallbackPtr,
                 dbExceptionCallbackPtr](std::vector<Posts> posts) mutable
                {
                    std::list<Posts> postsList{ posts.begin(), posts.end() };
                    Json::Value tmp;
                    std::list<Sprint> eventSprints;

                    for (auto& event : *resultJsonPtr)
                    {
                        tmp = event;
                        event = Json::Value{};
                        event["event"] = std::move(tmp);

                        eventSprints.clear();
                        std::copy_if(
                            sprintsList.cbegin(), sprintsList.cend(),
                            std::front_inserter(eventSprints),
                            [&event](const auto& sprint)
                            {
                                return sprint.getValueOfEventId() ==
                                       event["event"][Events::Cols::_id]
                                           .as<PrimaryKeyType>();
                            });

                        int32_t i{ 0 };
                        for (auto sprintIt{ std::cbegin(eventSprints) };
                             sprintIt != std::cend(eventSprints); i++)
                        {

                            // probably need to erase from first vector
                            event["sprints"][i] = sprintIt->toJson();

                            auto sprintPostIt{ std::find_if(
                                postsList.cbegin(), postsList.cend(),
                                [sprintIt](const Posts& post) {
                                    return post.getValueOfSprintId() ==
                                           sprintIt->getValueOfId();
                                }) };

                            event["sprints"][i]["post"] =
                                (sprintPostIt != postsList.cend()
                                     ? sprintPostIt->toJson()
                                     : Json::nullValue);

                            sprintIt = sprintsList.erase(sprintIt);
                            if (sprintPostIt != postsList.cend())
                                postsList.erase(sprintPostIt);
                        }
                    }
                    (*successCallbackPtr)(*resultJsonPtr);
                },

                *dbExceptionCallbackPtr); // TODO: macros
        },
        *dbExceptionCallbackPtr);
}
void expandSuggestionList(
    const Json::Value& suggestionListJson, int8_t voteSort,
    std::function<void(const Json::Value&)>&& successCallback,
    drogon::orm::DrogonDbExceptionCallback&& dbExceptionCallback)
{
    using namespace drogon_model::augventure_db;
    using namespace drogon::orm;

    auto resultJsonPtr{ std::make_shared<Json::Value>(
        std::move(suggestionListJson)) };
    auto successCallbackPtr{
        std::make_shared<std::function<void(const Json::Value&)>>(
            successCallback)
    };
    auto dbExceptionCallbackPtr{ std::make_shared<DrogonDbExceptionCallback>(
        dbExceptionCallback) };
    std::vector<PrimaryKeyType> suggestionIds{};
    std::vector<PrimaryKeyType> authorIds{};
    for (auto suggestionJson : *resultJsonPtr)
    {
        suggestionIds.push_back(
            suggestionJson[Suggestions::Cols::_id].as<PrimaryKeyType>());
        authorIds.push_back(
            suggestionJson[Suggestions::Cols::_author_id].as<PrimaryKeyType>());
    }

    auto dbClient{ drogon::app().getDbClient() };
    Mapper<Posts> postsMapper{ dbClient };
    postsMapper.findBy(
        Criteria{ Posts::Cols::_suggestion_id, CompareOperator::In,
                  suggestionIds },
        [dbClient, suggestionIds, resultJsonPtr, authorIds, successCallbackPtr,
         voteSort, dbExceptionCallbackPtr](auto postsVec)
        {
            // find posts success clause
            auto postsVecPtr{
                std::make_shared<typename std::decay<decltype(postsVec)>::type>(
                    postsVec)
            }; // to not copy in captures
            Mapper<PostMedia> postMediaMapper{ dbClient };
            postMediaMapper.findBy(
                Criteria{ PostMedia::Cols::_post_id, CompareOperator::In,
                          std::invoke(
                              [&postsVec]()
                              {
                                  std::vector<PrimaryKeyType> postIds;
                                  for (auto& post : postsVec)
                                      postIds.push_back(post.getValueOfId());
                                  return postIds;
                              }) },
                [dbClient, suggestionIds, postsVecPtr, resultJsonPtr, authorIds,
                 successCallbackPtr, voteSort,
                 dbExceptionCallbackPtr](auto postMediaVec)
                {
                    auto postMediaVecPtr{ std::make_shared<
                        typename std::decay<decltype(postMediaVec)>::type>(
                        postMediaVec) }; // to not copy in captures
                    // find post media success clause
                    Mapper<Votes> votesMapper{ dbClient };
                    votesMapper.findBy(
                        Criteria{ Votes::Cols::_suggestion_id,
                                  CompareOperator::In, suggestionIds },
                        [resultJsonPtr, authorIds, dbClient, successCallbackPtr,
                         voteSort, dbExceptionCallbackPtr, postsVecPtr,
                         postMediaVecPtr](auto votesVec)
                        {
                            // find votes success clause
                            Mapper<User> usersMapper{ dbClient };
                            usersMapper.findBy(
                                Criteria{ Users::Cols::_id, CompareOperator::In,
                                          authorIds },
                                [resultVec =
                                     std::vector<Json::Value>{
                                         resultJsonPtr->begin(),
                                         resultJsonPtr->end() },
                                 successCallbackPtr, voteSort,
                                 votesList = std::list<Vote>{ votesVec.begin(),
                                                              votesVec.end() },
                                 postsList =
                                     std::list<Posts>{ postsVecPtr->begin(),
                                                       postsVecPtr->end() },
                                 postMediaList =
                                     std::list<PostMedia>{
                                         postMediaVecPtr->begin(),
                                         postMediaVecPtr->end() }](
                                    auto authorsVec) mutable
                                {
                                    // find users success clause
                                    for (auto& responseEntryJson : resultVec)
                                    {
                                        // author
                                        auto suggestionAuthorIt{ std::find_if(
                                            authorsVec.begin(),
                                            authorsVec.end(),
                                            [authorId =
                                                 responseEntryJson
                                                     [Suggestions::Cols::
                                                          _author_id]
                                                         .as<PrimaryKeyType>()](
                                                auto user) {
                                                return user.getValueOfId() ==
                                                       authorId;
                                            }) };
                                        responseEntryJson["author"] =
                                            suggestionAuthorIt
                                                ->toJson(); // TODO: leave only
                                                            // needed columns

                                        // post and media
                                        auto postIt{ std::find_if(
                                            postsList.begin(), postsList.end(),
                                            [suggestionId =
                                                 responseEntryJson
                                                     [Suggestions::Cols::_id]
                                                         .as<PrimaryKeyType>()](
                                                auto post) {
                                                return post.getValueOfSuggestionId() ==
                                                       suggestionId;
                                            }) };
                                        responseEntryJson["post"] =
                                            postIt->toJson();
                                        responseEntryJson["post"]["media"] =
                                            Json::Value{
                                                Json::ValueType::arrayValue
                                            };
                                        for (auto postMediaIt{
                                                 postMediaList.begin() };
                                             postMediaIt !=
                                             postMediaList.end();)
                                        {
                                            if (postMediaIt
                                                    ->getValueOfPostId() ==
                                                postIt->getValueOfId())
                                            {
                                                responseEntryJson
                                                    ["post"]["media"]
                                                        .append(postMediaIt
                                                                    ->toJson());
                                                postMediaIt =
                                                    postMediaList.erase(
                                                        postMediaIt);
                                            }
                                            else
                                            {
                                                postMediaIt++;
                                            }
                                        }
                                        postsList.erase(postIt);

                                        // votes
                                        uint32_t votes{ 0 };
                                        for (auto voteIt{ votesList.begin() };
                                             voteIt != votesList.end();)
                                        {
                                            if (voteIt
                                                    ->getValueOfSuggestionId() ==
                                                responseEntryJson
                                                    [Suggestions::Cols::_id]
                                                        .as<PrimaryKeyType>())
                                            {
                                                votes +=
                                                    voteIt
                                                        ->getValueOfVoteValue();
                                                voteIt =
                                                    votesList.erase(voteIt);
                                            }
                                            else
                                            {
                                                voteIt++;
                                            }
                                        }
                                        responseEntryJson["votes"] = votes;
                                    }
                                    if (voteSort)
                                    {
                                        std::stable_sort(
                                            resultVec.begin(), resultVec.end(),
                                            [voteSort](auto&& s1, auto&& s2)
                                            {
                                                if (voteSort > 0)
                                                    return (
                                                        s1["votes"].asUInt() <
                                                        s2["votes"].asUInt());
                                                else
                                                    return (
                                                        s1["votes"].asUInt() >
                                                        s2["votes"].asUInt());
                                            });
                                    }
                                    Json::Value resultJson;
                                    for (auto suggestion : resultVec)
                                        resultJson.append(suggestion);
                                    (*successCallbackPtr)(resultJson);
                                },
                                *dbExceptionCallbackPtr);
                        },
                        *dbExceptionCallbackPtr);
                },
                *dbExceptionCallbackPtr);
        },
        dbExceptionCallback);
}

void createSeveralPostMedia(
    const std::vector<Json::Value>& jsons, uint32_t n,
    std::function<void(void)>&& successCallback,
    drogon::orm::DrogonDbExceptionCallback&& dbExceptionCallback)
{
    using namespace drogon_model::augventure_db;
    using namespace drogon::orm;

    auto successCallbackPtr{
        std::make_shared<typename std::decay<decltype(successCallback)>::type>(
            successCallback)
    };
    auto dbExceptionCallbackPtr{ std::make_shared<DrogonDbExceptionCallback>(
        dbExceptionCallback) };
    auto dbClient{ drogon::app().getDbClient() };
    Mapper<PostMedia> postMediaMapper{ dbClient };
    PostMedia postMedia{ jsons[jsons.size() - n] };
    postMediaMapper.insert(
        postMedia,
        [jsons, n, successCallbackPtr, dbExceptionCallbackPtr](auto) mutable
        {
            n--;
            if (n == 0)
            {
                (*successCallbackPtr)();
                return;
            }
            createSeveralPostMedia(jsons, n, std::move(*successCallbackPtr),
                                   std::move(*dbExceptionCallbackPtr));
        },
        dbExceptionCallback);
}

#pragma GCC diagnostic pop
