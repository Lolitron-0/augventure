#pragma once

#include "EventsControllerBase.h"
#include <drogon/HttpController.h>

#include "Events.h"
using namespace drogon;
using namespace drogon_model::augventure_db;
/**
 * @brief this class is created by the drogon_ctl command.
 * this class is a restful API controller for reading and writing the events
 * table.
 */

class EventsController : public drogon::HttpController<EventsController>,
                         public EventsControllerBase
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(EventsController::getOne, "/api/events/{1}", Get, Options,
                  "augventure::filters::LoginFilter");
    ADD_METHOD_TO(EventsController::updateOne, "/api/events/{1}", Put, Options,
                  "augventure::filters::LoginFilter");
    ADD_METHOD_TO(EventsController::deleteOne, "/api/events/{1}", Delete,
                  Options, "augventure::filters::LoginFilter");
    ADD_METHOD_TO(EventsController::get, "/api/events", Get, Options,
                  "augventure::filters::LoginFilter");
    ADD_METHOD_TO(EventsController::create, "/api/events", Post, Options,
                  "augventure::filters::LoginFilter");
    ADD_METHOD_TO(EventsController::finishVoting,
                  "/api/events/{1}/finish_voting", Patch, Options,
                  "augventure::filters::LoginFilter");
    ADD_METHOD_TO(EventsController::finishImplementing,
                  "/api/events/{1}/finish_implementing", Patch, Options,
                  "augventure::filters::LoginFilter");
    // ADD_METHOD_TO(EventsController::update,"/api/events",Put,Options,"augventure::filters::LoginFilter");
    METHOD_LIST_END

    void getOne(const HttpRequestPtr& req,
                std::function<void(const HttpResponsePtr&)>&& callback,
                Events::PrimaryKeyType&& id);
    void updateOne(const HttpRequestPtr& req,
                   std::function<void(const HttpResponsePtr&)>&& callback,
                   Events::PrimaryKeyType&& id);
    void deleteOne(const HttpRequestPtr& req,
                   std::function<void(const HttpResponsePtr&)>&& callback,
                   Events::PrimaryKeyType&& id);
    void get(const HttpRequestPtr& req,
             std::function<void(const HttpResponsePtr&)>&& callback);
    void create(const HttpRequestPtr& req,
                std::function<void(const HttpResponsePtr&)>&& callback);
    void finishVoting(const HttpRequestPtr& req,
                      std::function<void(const HttpResponsePtr&)>&& callback,
                      Events::PrimaryKeyType&& id);
    void finishImplementing(const HttpRequestPtr& req,
                      std::function<void(const HttpResponsePtr&)>&& callback,
                      Events::PrimaryKeyType&& id);
};
