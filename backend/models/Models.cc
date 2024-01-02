#include "Models.h"

void getFullEventData(
    const Json::Value &eventJson,
    std::function<void(const Json::Value &)> &&successCallback,
    std::function<void(const drogon::orm::DrogonDbException &)> &&dbExceptionCallback)
{
    using namespace drogon_model::augventure_db;
    using namespace drogon::orm;

    auto dbClient{drogon::app().getDbClient()};
    Mapper<Sprint> sprintMapper{dbClient};
    auto result{std::make_shared<Json::Value>()};
    (*result)["event"] = eventJson;
    sprintMapper.orderBy(Sprints::Cols::_start, SortOrder::ASC)
        .findBy(
            Criteria{Sprints::Cols::_event_id,
                     CompareOperator::EQ,
                     eventJson[Events::Cols::_id].as<PrimaryKeyType>()},
            [successCallback, dbExceptionCallback, result](std::vector<Sprint> sprintHistory)
            {
                auto dbClient{drogon::app().getDbClient()};
                Mapper<Posts> postsMapper{dbClient};
                postsMapper.findBy(
                    Criteria{Posts::Cols::_sprint_id,
                             CompareOperator::In,
                             std::invoke(
                                 [&sprintHistory]() // IIFE so won't
                                 // invalidate
                                 {
                                     std::vector<int> ids{};
                                     for (const auto &sprint : sprintHistory)
                                         ids.push_back(sprint.getValueOfId());
                                     return ids;
                                 })},
                    [sprintHistory, result, successCallback](std::vector<Posts> posts)
                    {
                        for (auto it{std::cbegin(sprintHistory)}; it != std::cend(sprintHistory);
                             it++)
                        {
                            (*result)["sprints"]
                                     [(int32_t) std::distance(std::cbegin(sprintHistory), it)]
                                = it->toJson();

                            auto relatedPost{std::find_if(std::begin(posts),
                                                          std::end(posts),
                                                          [it](const Posts &post) {
                                                              return post.getValueOfSprintId()
                                                                     == it->getValueOfId();
                                                          })};
                            (*result)["sprints"][(int32_t) std::distance(std::cbegin(sprintHistory),
                                                                         it)]["post"]
                                = (relatedPost != std::end(posts) ? relatedPost->toJson()
                                                                  : Json::nullValue);
                        }
                        successCallback(*result);
                    },

                    dbExceptionCallback);
            },
            dbExceptionCallback);
}
