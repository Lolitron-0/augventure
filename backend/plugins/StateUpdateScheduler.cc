/**
 *
 *  Scheduler.cc
 *
 */

#include "StateUpdateScheduler.h"
#include <chrono>
#include <drogon/orm/Exception.h>
#include <memory>
#include <thread>

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
            while (this->m_ThreadAlive)
            {
                std::cout << "hello\n";
                std::this_thread::sleep_for(2s);
            }
        });
}

void StateUpdateScheduler::updateClosestTasks()
{
    static bool initLaunch = true;
    using namespace drogon_model::augventure_db;

    if (initLaunch)
    {
        this->_scheduleStateChange<Event>(Events::Cols::_state,
                                          Events::Cols::_start, "scheduled",
                                          "in_progress");
    }

    initLaunch = false;
}

void StateUpdateScheduler::shutdown()
{
	m_ThreadAlive = false; // hehe no mutex goes brr
	m_Thread->join();
	LOG_INFO << "StateUpdateScheduler thread stopped";
}

} // namespace plugins
} // namespace augventure
