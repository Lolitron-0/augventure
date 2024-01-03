#include "Models.h"
#include "utils/Macros.h"
#include <drogon/orm/Exception.h>
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
	expandEventList(std::move(eventList), [successCallbackPtr](auto result)
			{
				(*successCallbackPtr)(result[0]);
			}, std::forward<decltype(dbExceptionCallback)>(dbExceptionCallback));
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
