/**
 *
 *  Scheduler.h
 *
 */

#pragma once

#include "Models.h"
#include <drogon/drogon.h>
#include <drogon/orm/Criteria.h>
#include <drogon/orm/Exception.h>
#include <drogon/plugins/Plugin.h>
#include <exception>
#include <functional>
#include <memory>
#include <thread>
#include <trantor/utils/Date.h>
#include <tuple>

namespace augventure
{
namespace plugins
{

class StateUpdateScheduler : public drogon::Plugin<StateUpdateScheduler>
{
public:
    enum class TaskType
    {
        EventStart,
        SprintEnd
    };
    using UTCMark = trantor::Date;

    StateUpdateScheduler() {}
    void initAndStart(const Json::Value& config) override;

    void updateClosestTasks();
    template<typename T>
    void updateTaskType(const TaskType &type, T entityToUpdate)
    {

        using namespace drogon_model::augventure_db;
        using namespace drogon::orm;

        auto [colName, oldState, newState] = _getArgsFromTaskType(type);
        auto mark{dateFromJsonString(entityToUpdate.toJson()[colName].asString())};
        for (auto& task : m_ClosestSheduledJobs)
        {
            if (type == task.taskType && mark < task.mark)
            {
                task.mark = mark;
                task.jobCallback = [entityToUpdate = entityToUpdate, newState = newState]() mutable
                {
                    auto dbClient{ drogon::app().getDbClient() };
                    auto mapper{ Mapper<T>{ dbClient } };
					
					entityToUpdate.setState(newState);
					mapper.update(entityToUpdate);
                };
            }
        }
    }

    void shutdown() override;

private:
    template <typename T> void _scheduleStateChange(const TaskType& type)
    {

        using namespace drogon_model::augventure_db;
        using namespace drogon::orm;

        auto dbClient{ drogon::app().getDbClient() };

        auto mapper{ Mapper<T>{ dbClient } };
        size_t page{ 1 };
        auto now{ trantor::Date::now() };
        auto [colName, waitState, newState] = _getArgsFromTaskType(type);
        bool stopPagination{ false }, waitBeforeNextPage{ false };
        while (!stopPagination)
        {
            try
            {
                waitBeforeNextPage = true;
                auto scheduledEntities{
                    mapper.orderBy(colName)
                        .paginate(page, 1000) // avoid memory overflow
                        .findBy(Criteria{ Events::Cols::_state,
                                          CompareOperator::EQ, waitState })
                };

                if (!scheduledEntities.size()) // pagination end
                {
                    stopPagination = true;
                    return;
                }

                for (const auto& entity : scheduledEntities)
                {
                    if (entity.getValueOfStart().secondsSinceEpoch() -
                            now.secondsSinceEpoch() >
                        60)
                    {
                        m_ClosestSheduledJobs.push_back(
                            { .taskType = type,
                              .mark = entity.getValueOfStart(),
                              .jobCallback =
                                  [entity = entity,
                                   newState = newState]() mutable // ok because
                              // will be
                              // called only once
                              {
                                  auto dbClient{ drogon::app().getDbClient() };
                                  Mapper<T> mapper{ dbClient };
                                  entity.setState(newState);
                                  mapper.update(entity);
                              } });
                        stopPagination = true;
                        return;
                    }
                }
                page++;
                waitBeforeNextPage = false;
            }
            catch (...) // no events at all
            {
                return;
            }
        }
    }

    void _processMistimedEntities() const;
    // returns UTC mark column name, previous state and desired state
    std::tuple<std::string, std::string, std::string>
    _getArgsFromTaskType(const TaskType& type)
    {
        using namespace drogon_model::augventure_db;

        switch (type)
        {
        case TaskType::EventStart:
            return std::make_tuple(Event::Cols::_start, "scheduled",
                                   "in_progress");
        default:
            throw std::logic_error("Not implemented");
        }
    }

private:
    struct ScheduledTask
    {
        TaskType taskType;
        UTCMark mark;
        std::function<void(void)> jobCallback;
    };

private:
    std::unique_ptr<std::thread> m_Thread;
    bool m_ThreadAlive{ true };
    std::vector<ScheduledTask> m_ClosestSheduledJobs;
    static constexpr int32_t s_RefreshPeriodSeconds{ 5 };
};

} // namespace plugins
} // namespace augventure
