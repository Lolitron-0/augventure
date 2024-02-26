#pragma once

#include "UsersControllerBase.h"
#include <drogon/HttpController.h>

#include "Users.h"
using namespace drogon;
using namespace drogon_model::augventure_db;

class UsersController : public drogon::HttpController<UsersController>,
                        public UsersControllerBase
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(UsersController::getOne, "/api/users/{1}", Get, Options,
                  "augventure::filters::LoginFilter");
    ADD_METHOD_TO(UsersController::updateOne, "/api/users/{1}", Put, Options,
                  "augventure::filters::LoginFilter");
    ADD_METHOD_TO(UsersController::deleteOne, "/api/users/{1}", Delete, Options,
                  "augventure::filters::LoginFilter");
    ADD_METHOD_TO(UsersController::get, "/api/users", Get, Options,
                  "augventure::filters::LoginFilter");
    ADD_METHOD_TO(UsersController::create, "/api/users", Post, Options,
                  "augventure::filters::LoginFilter");
    ADD_METHOD_TO(UsersController::profile, "/api/users/me", Get, Options,
                  "augventure::filters::LoginFilter");
    ADD_METHOD_TO(UsersController::profileUpdate, "/api/users/me", Put, Options,
                      "augventure::filters::LoginFilter");
    ADD_METHOD_TO(UsersController::passwordReset, "api/users/me/password_reset",
                  Put, "augventure::filters::LoginFilter");
    ADD_METHOD_TO(UsersController::uploadPfp, "/api/users/me/upload_pfp", Put,
                  Options, "augventure::filters::LoginFilter");
    // ADD_METHOD_TO(UsersController::update,"/api/users",Put,Options,"augventure::filters::LoginFilter");
    METHOD_LIST_END

    void getOne(const HttpRequestPtr& req,
                std::function<void(const HttpResponsePtr&)>&& callback,
                Users::PrimaryKeyType&& id);
    void updateOne(const HttpRequestPtr& req,
                   std::function<void(const HttpResponsePtr&)>&& callback,
                   Users::PrimaryKeyType&& id);
    void deleteOne(const HttpRequestPtr& req,
                   std::function<void(const HttpResponsePtr&)>&& callback,
                   Users::PrimaryKeyType&& id);
    void get(const HttpRequestPtr& req,
             std::function<void(const HttpResponsePtr&)>&& callback);
    void create(const HttpRequestPtr& req,
                std::function<void(const HttpResponsePtr&)>&& callback);
    void profile(const drogon::HttpRequestPtr& req,
                 drogon::AdviceCallback&& callback);
    void profileUpdate(const drogon::HttpRequestPtr& req,
                 drogon::AdviceCallback&& callback);
    void passwordReset(const HttpRequestPtr& req,
                       std::function<void(const HttpResponsePtr&)>&& callback);
    void uploadPfp(const HttpRequestPtr& req,
                   std::function<void(const HttpResponsePtr&)>&& callback);
};
