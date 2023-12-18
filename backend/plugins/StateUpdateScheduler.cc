/**
 *
 *  Scheduler.cc
 *
 */

#include "StateUpdateScheduler.h"
#include "Events.h"
#include "Models.h"
#include "Sprints.h"
#include <chrono>
#include <drogon/orm/Criteria.h>
#include <drogon/orm/Exception.h>
#include <iterator>
#include <memory>
#include <thread>
#include <trantor/utils/Date.h>
#include <utility>

using namespace drogon;
using namespace augventure::plugins;

namespace augventure
{
namespace plugins
{

void StateUpdateScheduler::initAndStart(const Json::Value& config)
{
    this->_initTaskQueue();
    LOG_INFO << "StateUpdateScheduler: loaded closest tasks";
    m_Thread = std::make_unique<std::thread>(
        [this]()
        {
            using namespace drogon_model::augventure_db;
            using namespace drogon::orm;

            auto now{ trantor::Date::now() };
            auto dbClient{ drogon::app().getDbClient() };
            auto eventMapper{ Mapper<Events>{ dbClient } };
            auto sprintMapper{ Mapper<Sprints>{ dbClient } };

            while (this->m_ThreadAlive)
            {
                now = trantor::Date::now();
                auto it = std::begin(m_TaskQueue);
                for (; it != std::end(m_TaskQueue);)
                {
                    if (it->timestamp.secondsSinceEpoch() -
                            now.secondsSinceEpoch() <=
                        0)
                    {
                        switch (it->type)
                        {
                        case TaskType::EventStart:
                            eventMapper.updateBy({ Events::Cols::_state },
                                                 Criteria{ Events::Cols::_id,
                                                           CompareOperator::EQ,
                                                           it->objectId },
                                                 "in_progress");
                            break;
                        case TaskType::SprintEnd:
                            throw std::logic_error("Not implemented");
                            break;
                        }
                        it = m_TaskQueue.erase(it);
                        LOG_TRACE << (it == m_TaskQueue.end());
                    }
                    else
                    {
                        std::advance(it, 1);
                    }
                }
                std::this_thread::sleep_for(
                    std::chrono::seconds{ s_RefreshPeriodSeconds });
            }
        });
}

void StateUpdateScheduler::schedule(const TaskType& type, const UTCMark& time,
                                    const PrimaryKeyType& objectKey)
{
    m_TaskQueue.insert(
        { .timestamp = time, .objectId = objectKey, .type = type });
}

void StateUpdateScheduler::removeTaskByKey(const PrimaryKeyType& objectKey)
{
    auto it{ std::find_if(std::begin(m_TaskQueue), std::end(m_TaskQueue),
                          [objectKey](const ScheduledTask& task)
                          { return task.objectId == objectKey; }) };
    if (it == std::end(m_TaskQueue))
        return;
    m_TaskQueue.erase(it);
}

void StateUpdateScheduler::_initTaskQueue()
{
    using namespace drogon_model::augventure_db;
    using namespace drogon::orm;

    auto dbClient{ drogon::app().getDbClient() };
    auto eventMapper{ Mapper<Events>{ dbClient } };

    size_t page{ 1 };
    while (true)
    {
        auto scheduledEvents{ eventMapper.paginate(page, 10000)
                                  .findBy(Criteria{ Events::Cols::_state,
                                                    CompareOperator::EQ,
                                                    "scheduled" }) };
        if (scheduledEvents.empty())
            return;

        for (const auto& event : scheduledEvents)
        {
            m_TaskQueue.insert({ .timestamp = event.getValueOfStart(),
                                 .objectId = event.getValueOfId(),
                                 .type = TaskType::EventStart });
        }
        page++;
    }
}

void StateUpdateScheduler::shutdown()
{
    m_ThreadAlive = false; // hehe no mutex goes brr
    m_Thread->join();
    LOG_INFO << "StateUpdateScheduler thread stopped";
}

} // namespace plugins
} // namespace augventure
