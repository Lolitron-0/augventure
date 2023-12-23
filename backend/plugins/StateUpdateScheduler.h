/**
 *
 *  Scheduler.h
 *
 */

#pragma once

#include "Events.h"
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
    enum class TaskType : int8_t
    {
        EventStart,
        SprintEnd
    };
    using UTCMark = trantor::Date;

    StateUpdateScheduler() {}
    void initAndStart(const Json::Value& config) override;

    void schedule(const TaskType& type, const UTCMark& time,
                  const PrimaryKeyType& objectKey);

	void removeTaskByKey(const PrimaryKeyType& objectKey);

    void shutdown() override;

private:
    void _initTaskQueue();

private:
    struct ScheduledTask
    {
        UTCMark timestamp;
        drogon_model::augventure_db::Events::PrimaryKeyType objectId;
        TaskType type;

        bool operator<(const ScheduledTask& other) const
        {
            return timestamp < other.timestamp
                   || (timestamp == other.timestamp && objectId < other.objectId)
                   || (objectId == other.objectId && type < other.type);
        }
    };

private:
    std::set<ScheduledTask> m_TaskQueue;
    std::unique_ptr<std::thread> m_Thread;
    std::mutex m_Mutex;
    bool m_ThreadAlive{ true };
    static constexpr int32_t s_RefreshPeriodSeconds{ 1 };
};

} // namespace plugins
} // namespace augventure
