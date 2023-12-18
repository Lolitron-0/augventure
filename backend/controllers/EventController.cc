#include "EventController.h"
#include "Models.h"
#include "plugins/JWTService.h"
#include "plugins/StateUpdateScheduler.h"
#include "utils/Macros.h"
#include <drogon/HttpAppFramework.h>
#include <drogon/HttpTypes.h>
#include <drogon/orm/Criteria.h>
#include <drogon/orm/Exception.h>
#include <drogon/orm/Mapper.h>
#include <iterator>

namespace augventure
{
namespace controllers
{
// Add definition of your processing function here

void EventController::createEvent(
    const drogon::HttpRequestPtr& req, drogon::AdviceCallback&& callback,
    drogon_model::augventure_db::Event&& newEventData)
{
    using namespace drogon_model::augventure_db;
    using namespace drogon::orm;

    auto dbClient{ drogon::app().getDbClient() };
    Mapper<Event> mapper{ dbClient };
    auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };
    auto currentUserId{ CURRENT_USER_ID(req) };

    newEventData.setAuthorId(currentUserId);
    mapper.insert(
        newEventData,
        [=](Event event)
        {
            using namespace augventure::plugins;
            drogon::app().getPlugin<StateUpdateScheduler>()->schedule(
                StateUpdateScheduler::TaskType::EventStart,
                event.getValueOfStart(), event.getValueOfId());
            (*callbackPtr)(drogon::HttpResponse::newHttpResponse(
                drogon::k200OK, drogon::CT_NONE));
        },
        [=](const DrogonDbException& e)
        {
            LOG_TRACE << e.base().what();
            auto resp{ HttpResponse::newHttpResponse(k400BadRequest,
                                                     CT_TEXT_PLAIN) };
            resp->setBody("database exception: " +
                          (std::string)e.base().what());
            (*callbackPtr)(resp);
        });
}

void EventController::listEvents(const drogon::HttpRequestPtr& req,
                                 drogon::AdviceCallback&& callback)
{
    using namespace drogon_model::augventure_db;
    using namespace drogon::orm;

    auto dbClient{ drogon::app().getDbClient() };
    Mapper<Event> mapper{ dbClient };
    auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };
    auto currentUserId{ CURRENT_USER_ID(req) };

    mapper.findBy(
        Criteria{ Event::Cols::_author_id, CompareOperator::EQ, currentUserId },
        [=](std::vector<Event> events)
        {
            Json::Value respJson;
            for (auto it = events.cbegin(); it != events.cend(); it++)
            {
                respJson["events"][(int32_t)std::distance(events.cbegin(),
                                                          it)] = it->toJson();
            }
            (*callbackPtr)(drogon::HttpResponse::newHttpJsonResponse(respJson));
        },
        [=](const DrogonDbException& e)
        {
            LOG_TRACE << e.base().what();
            auto resp{ HttpResponse::newHttpResponse(k400BadRequest,
                                                     CT_TEXT_PLAIN) };
            resp->setBody("database exception: " +
                          (std::string)e.base().what());
            (*callbackPtr)(resp);
        });
}

void EventController::deleteEvent(const drogon::HttpRequestPtr& req,
                                  drogon::AdviceCallback&& callback,
                                  PrimaryKeyType eventId)
{
    using namespace drogon_model::augventure_db;
    using namespace drogon::orm;

    auto dbClient{ drogon::app().getDbClient() };
    Mapper<Event> mapper{ dbClient };
    auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };
    auto currentUserId{ CURRENT_USER_ID(req) };

    mapper.findByPrimaryKey(
        eventId,
        [=](Event eventToDelete)
        {
            if (eventToDelete.getValueOfAuthorId() == currentUserId)
            {
                drogon::app()
                    .getPlugin<augventure::plugins::StateUpdateScheduler>()
                    ->removeTaskByKey(eventId);

                Mapper<Event> deleteMapper{ dbClient };
                deleteMapper.deleteByPrimaryKey(
                    eventId,
                    [=](size_t)
                    {
                        auto resp{ HttpResponse::newHttpResponse(k200OK,
                                                                 CT_NONE) };
                        (*callbackPtr)(resp);
                    },
                    [=](const DrogonDbException& e)
                    {
                        LOG_TRACE << e.base().what();
                        auto resp{ HttpResponse::newHttpResponse(
                            k400BadRequest, CT_TEXT_PLAIN) };
                        resp->setBody("database exception: " +
                                      (std::string)e.base().what());
                        (*callbackPtr)(resp);
                    });
            }
        },
        [=](const DrogonDbException& e)
        {
            LOG_TRACE << e.base().what();
            auto resp{ HttpResponse::newHttpResponse(k400BadRequest,
                                                     CT_TEXT_PLAIN) };
            resp->setBody("database exception: " +
                          (std::string)e.base().what());
            (*callbackPtr)(resp);
        });
}

} // namespace controllers
} // namespace augventure
