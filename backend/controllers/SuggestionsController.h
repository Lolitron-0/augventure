#pragma once

#include "Models.h"
#include "SuggestionsControllerBase.h"
#include <drogon/HttpController.h>

#include "Suggestions.h"
using namespace drogon;
using namespace drogon_model::augventure_db;
/**
 * @brief this class is created by the drogon_ctl command.
 * this class is a restful API controller for reading and writing the
 * suggestions table.
 */

class SuggestionsController
    : public drogon::HttpController<SuggestionsController>,
      public SuggestionsControllerBase
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(SuggestionsController::getOne, "/api/suggestions/{1}", Get,
                  Options, "augventure::filters::LoginFilter");
    ADD_METHOD_TO(SuggestionsController::updateOne, "/api/suggestions/{1}", Put,
                  Options, "augventure::filters::LoginFilter");
    ADD_METHOD_TO(SuggestionsController::vote, "/api/suggestions/{1}/vote", Put,
                  Options, "augventure::filters::LoginFilter");
    ADD_METHOD_TO(SuggestionsController::deleteOne, "/api/suggestions/{1}",
                  Delete, Options, "augventure::filters::LoginFilter");
    ADD_METHOD_TO(SuggestionsController::get, "/api/suggestions", Get, Options,
                  "augventure::filters::LoginFilter");
    ADD_METHOD_TO(SuggestionsController::create, "/api/suggestions", Post,
                  Options, "augventure::filters::LoginFilter");
    ADD_METHOD_TO(SuggestionsController::addMedia, "/api/suggestions/{1}/add_media", Put,
                  Options, "augventure::filters::LoginFilter");
    // ADD_METHOD_TO(SuggestionsController::update,"/api/suggestions",Put,Options,"augventure::filters::LoginFilter");
    METHOD_LIST_END

    void getOne(const HttpRequestPtr& req,
                std::function<void(const HttpResponsePtr&)>&& callback,
                Suggestions::PrimaryKeyType&& id);
    void updateOne(const HttpRequestPtr& req,
                   std::function<void(const HttpResponsePtr&)>&& callback,
                   Suggestions::PrimaryKeyType&& id);
    void vote(const HttpRequestPtr& req,
                   std::function<void(const HttpResponsePtr&)>&& callback,
                   Suggestions::PrimaryKeyType&& id);
    void deleteOne(const HttpRequestPtr& req,
                   std::function<void(const HttpResponsePtr&)>&& callback,
                   Suggestions::PrimaryKeyType&& id);
    void get(const HttpRequestPtr& req,
             std::function<void(const HttpResponsePtr&)>&& callback);
    void create(const HttpRequestPtr& req,
                std::function<void(const HttpResponsePtr&)>&& callback);
    void addMedia(const HttpRequestPtr& req,
                std::function<void(const HttpResponsePtr&)>&& callback, PrimaryKeyType&& id);
};
