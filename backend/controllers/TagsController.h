#pragma once

#include <drogon/HttpController.h>
#include "TagsControllerBase.h"

#include "Tags.h"
using namespace drogon;
using namespace drogon_model::augventure_db;

class TagsController: public drogon::HttpController<TagsController>, public TagsControllerBase
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(TagsController::getOne,"/api/tags/{1}",Get,Options,"augventure::filters::LoginFilter");
    ADD_METHOD_TO(TagsController::updateOne,"/api/tags/{1}",Put,Options,"augventure::filters::LoginFilter");
    ADD_METHOD_TO(TagsController::deleteOne,"/api/tags/{1}",Delete,Options,"augventure::filters::LoginFilter");
    ADD_METHOD_TO(TagsController::get,"/api/tags",Get,Options,"augventure::filters::LoginFilter");
    ADD_METHOD_TO(TagsController::create,"/api/tags",Post,Options,"augventure::filters::LoginFilter");
    //ADD_METHOD_TO(TagsController::update,"/api/tags",Put,Options,"augventure::filters::LoginFilter");
    METHOD_LIST_END
     
    void getOne(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                Tags::PrimaryKeyType &&id);
    void updateOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   Tags::PrimaryKeyType &&id);
    void deleteOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   Tags::PrimaryKeyType &&id);
    void get(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback);
    void create(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback);

};
