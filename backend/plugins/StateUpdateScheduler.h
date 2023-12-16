/**
 *
 *  Scheduler.h
 *
 */

#pragma once

#include "Models.h"
#include <drogon/drogon.h>
#include <drogon/orm/Criteria.h>
#include <drogon/plugins/Plugin.h>
#include <functional>
#include <memory>
#include <thread>
#include <trantor/utils/Date.h>

namespace augventure
{
namespace plugins
{

class StateUpdateScheduler : public drogon::Plugin<StateUpdateScheduler>
{
public:
    StateUpdateScheduler() {}
    void initAndStart(const Json::Value& config) override;

    void updateClosestTasks();

    void shutdown() override;

private:
    template <typename T>
    void _scheduleStateChange(const std::string& colName,
                              const std::string& timeCol,
                              const std::string& oldState,
                              const std::string& newState)
    {

        using namespace drogon_model::augventure_db;
        using namespace drogon::orm;

        auto dbClient{ drogon::app().getDbClient() };
        Mapper<T> mapper{ dbClient };
        size_t page{ 1 };
        auto now = trantor::Date::now();
        while (true)
        {
            try
            {
                auto schedEvents{
                    mapper.orderBy(T::Cols::_start)
                        .paginate(page, 1000) // avoid memory overflow
                        .findBy(Criteria{ Events::Cols::_state,
                                          CompareOperator::EQ, oldState })
                };

                if (!schedEvents.size()) // pagination end
                    return;

                for (const auto& event : schedEvents)
                {
                    if (event.getValueOfStart().roundSecond() >= now)
                    {
                        m_ClosestSheduledJobs.push_back(std::make_pair(
                            event.getValueOfStart(),
                            [mapper, event = event,
                             newState]() mutable // ok because will be
                                                 // called only once
                            {
                                event.setState(newState);
                                mapper.update(event);
                            }));
                        // TODO: process events with same date
                        return;
                    }
                }
                page++;
            }
            catch (...) // no events at all
            {
                return;
            }
        }
    }

    std::unique_ptr<std::thread> m_Thread;
    bool m_ThreadAlive{ true };
    using UTCMark = trantor::Date;
    std::vector<std::pair<const UTCMark, std::function<void(void)>>>
        m_ClosestSheduledJobs;
};

} // namespace plugins
} // namespace augventure
