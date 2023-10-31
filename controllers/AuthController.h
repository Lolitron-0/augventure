#pragma once
#pragma once

#include <drogon/HttpController.h>
#include "models/Users.h"

using namespace drogon;

namespace augventure {
    struct UserSignUpInfo;

    namespace controllers {
        class AuthController : public drogon::HttpController<AuthController>
        {
        public:
            METHOD_LIST_BEGIN
                // use METHOD_ADD to add your custom processing function here;
                // METHOD_ADD(AuthController::get, "/{2}/{1}", Get); // path is /augventure/AuthController/{arg2}/{arg1}
                // METHOD_ADD(AuthController::your_method_name, "/{1}/{2}/list", Get); // path is /augventure/AuthController/{arg1}/{arg2}/list
                // ADD_METHOD_TO(AuthController::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list

                ADD_METHOD_TO(AuthController::signup, "/sign_up", Post, "augventure::filters::UserExistsFilter");
                ADD_METHOD_TO(AuthController::login, "/log_in", Post);
                ADD_METHOD_TO(AuthController::currentUserTest, "/profile", Get, "augventure::filters::LoginFilter");
                ADD_METHOD_TO(AuthController::passwordReset, "/password_reset", Post, "augventure::filters::LoginFilter");

            METHOD_LIST_END
                // your declaration of processing function maybe like this:
                // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
                // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;

                void signup(drogon_model::augventure_db::User&& newUserData, drogon::AdviceCallback&& callback);
                void login(const drogon::HttpRequestPtr& req, drogon::AdviceCallback&& callback,
                    drogon_model::augventure_db::User&& loginUserData);
                void currentUserTest(const drogon::HttpRequestPtr& req, drogon::AdviceCallback&& callback);
                void passwordReset(const drogon::HttpRequestPtr& req, drogon::AdviceCallback&& callback);
        };
    }
}
