#pragma once

#include "PostsControllerBase.h"
#include <drogon/HttpController.h>

#include "Posts.h"
using namespace drogon;
using namespace drogon_model::augventure_db;

class PostsController : public drogon::HttpController<PostsController>,
                        public PostsControllerBase
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(PostsController::getOne, "/api/posts/{1}", Get, Options,
                  "augventure::filters::LoginFilter");
    ADD_METHOD_TO(PostsController::updateOne, "/api/posts/{1}", Put, Options,
                  "augventure::filters::LoginFilter");
    ADD_METHOD_TO(PostsController::deleteOne, "/api/posts/{1}", Delete, Options,
                  "augventure::filters::LoginFilter");
    ADD_METHOD_TO(PostsController::get, "/api/posts", Get, Options,
                  "augventure::filters::LoginFilter");
    ADD_METHOD_TO(PostsController::create, "/api/posts", Post, Options,
                  "augventure::filters::LoginFilter");
    ADD_METHOD_TO(PostsController::addMedia, "/api/posts/{1}/add_media", Put,
                  Options, "augventure::filters::LoginFilter");

    // ADD_METHOD_TO(PostsController::update,"/api/posts",Put,Options,"augventure::filters::LoginFilter");
    METHOD_LIST_END

    void getOne(const HttpRequestPtr& req,
                std::function<void(const HttpResponsePtr&)>&& callback,
                Posts::PrimaryKeyType&& id);
    void updateOne(const HttpRequestPtr& req,
                   std::function<void(const HttpResponsePtr&)>&& callback,
                   Posts::PrimaryKeyType&& id);
    void deleteOne(const HttpRequestPtr& req,
                   std::function<void(const HttpResponsePtr&)>&& callback,
                   Posts::PrimaryKeyType&& id);
    void get(const HttpRequestPtr& req,
             std::function<void(const HttpResponsePtr&)>&& callback);
    void create(const HttpRequestPtr& req,
                std::function<void(const HttpResponsePtr&)>&& callback);
    void addMedia(const HttpRequestPtr& req,
                  std::function<void(const HttpResponsePtr&)>&& callback,
                  Posts::PrimaryKeyType&& id);
};
