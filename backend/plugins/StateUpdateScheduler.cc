/**
 *
 *  Scheduler.cc
 *
 */

#include "StateUpdateScheduler.h"
#include <chrono>
#include <drogon/orm/Exception.h>
#include <iterator>
#include <memory>
#include <thread>
#include <trantor/utils/Date.h>

using namespace drogon;
using namespace augventure::plugins;

namespace augventure
{
namespace plugins
{

void StateUpdateScheduler::initAndStart(const Json::Value& config)
{

    this->updateClosestTasks();
    LOG_INFO << "StateUpdateScheduler: loaded closest tasks";
    m_Thread = std::make_unique<std::thread>(
        [this]()
        {
            using namespace std::literals::chrono_literals;
            auto now{ trantor::Date::now() };
            bool needUpdateJobList{ false };
            while (this->m_ThreadAlive)
            {
                needUpdateJobList = false;
                for (auto it{ std::begin(m_ClosestSheduledJobs) };
                     it != std::end(m_ClosestSheduledJobs);)
                {
                    if (it->mark.secondsSinceEpoch() - now.secondsSinceEpoch() <= 0)
                    {
                        it->jobCallback();
                        m_ClosestSheduledJobs.erase(it);
                        needUpdateJobList = true;
                    }
                    else
                    {
                        it++;
                    }
                }
                if (needUpdateJobList)
                    this->updateClosestTasks();
                now = now.after(s_RefreshPeriodSeconds);
                std::this_thread::sleep_for(
                    std::chrono::seconds{ s_RefreshPeriodSeconds });
            }
        });
}

void StateUpdateScheduler::updateClosestTasks()
{
    using namespace drogon_model::augventure_db;
    this->_processMistimedEntities();

    this->_scheduleStateChange<Event>(TaskType::EventStart); //TODO: get other args from TaskType
}

void StateUpdateScheduler::_processMistimedEntities() const
{

    using namespace drogon_model::augventure_db;
    using namespace drogon::orm;

    auto dbClient{ drogon::app().getDbClient() };
    Mapper<Events> mapper{ dbClient };
    auto now{ trantor::Date::now() };
    auto schedEvents{mapper.orderBy(Events::Cols::_start)
                         .findBy(Criteria{Events::Cols::_state, CompareOperator::EQ, "scheduled"}
                                 // there should not be many unprocessed events to cause
                                 // overflow (as they can't be created if server is offline)
                                 )};
    for (auto &event : schedEvents)
    {
        auto b = now.secondsSinceEpoch();
        if (event.getValueOfStart().secondsSinceEpoch() - now.secondsSinceEpoch() <= 60)
        {
            auto dbClient{drogon::app().getDbClient()};
            Mapper<Events> mapper{dbClient};
            event.setState("in_progress");
            mapper.update(
                event, [](size_t) {}, [](const DrogonDbException &) {});
        }
        else // no mistimed further
            return;
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
