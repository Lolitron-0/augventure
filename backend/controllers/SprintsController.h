#pragma once

#include <drogon/HttpController.h>
#include "SprintsControllerBase.h"

#include "Sprints.h"
using namespace drogon;
using namespace drogon_model::augventure_db;

class SprintsController: public drogon::HttpController<SprintsController>, public SprintsControllerBase
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(SprintsController::getOne,"/api/sprints/{1}",Get,Options,"augventure::filters::LoginFilter");
    ADD_METHOD_TO(SprintsController::updateOne,"/api/sprints/{1}",Put,Options,"augventure::filters::LoginFilter");
    ADD_METHOD_TO(SprintsController::deleteOne,"/api/sprints/{1}",Delete,Options,"augventure::filters::LoginFilter");
    ADD_METHOD_TO(SprintsController::get,"/api/sprints",Get,Options,"augventure::filters::LoginFilter");
    ADD_METHOD_TO(SprintsController::create,"/api/sprints",Post,Options,"augventure::filters::LoginFilter");
    //ADD_METHOD_TO(SprintsController::update,"/api/sprints",Put,Options,"augventure::filters::LoginFilter");
    METHOD_LIST_END
     
    void getOne(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                Sprints::PrimaryKeyType &&id);
    void updateOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   Sprints::PrimaryKeyType &&id);
    void deleteOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   Sprints::PrimaryKeyType &&id);
    void get(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback);
    void create(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback);

};
