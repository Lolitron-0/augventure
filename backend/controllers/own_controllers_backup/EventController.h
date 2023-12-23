#pragma once

#include "models/Models.h"
#include <drogon/HttpController.h>
#include "utils/Utils.h"

using namespace drogon;

namespace augventure
{
namespace controllers
{
class EventController : public drogon::HttpController<EventController>
{

public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    // METHOD_ADD(EventController::get, "/{2}/{1}", Get); // path is
    // /augventure/controllers/EventController/{arg2}/{arg1}
    // METHOD_ADD(EventController::your_method_name, "/{1}/{2}/list", Get); //
    // path is /augventure/controllers/EventController/{arg1}/{arg2}/list
    // ADD_METHOD_TO(EventController::your_method_name,
    // "/absolute/path/{1}/{2}/list", Get); // path is
    // /absolute/path/{arg1}/{arg2}/list
    ADD_METHOD_TO(EventController::createEvent, "api/events/create", Post,
                  "augventure::filters::LoginFilter");
    ADD_METHOD_TO(EventController::listEvents, "api/events", Get,
                  "augventure::filters::LoginFilter");
    ADD_METHOD_TO(EventController::deleteEvent, "api/events/delete/{eventId}", Post,
                  "augventure::filters::LoginFilter");

    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const
    // HttpResponsePtr &)> &&callback, int p1, std::string p2); void
    // your_method_name(const HttpRequestPtr& req, std::function<void (const
    // HttpResponsePtr &)> &&callback, double p1, int p2) const;
    void createEvent(const drogon::HttpRequestPtr& req,
                     drogon::AdviceCallback&& callback,
                     drogon_model::augventure_db::Event&& newEventData);
    void listEvents(const drogon::HttpRequestPtr& req,
                    drogon::AdviceCallback&& callback, EventsFilteringData&& filteringData);
    void deleteEvent(const drogon::HttpRequestPtr& req,
                     drogon::AdviceCallback&& callback, PrimaryKeyType&& eventId);
};
} // namespace controllers
} // namespace augventure
