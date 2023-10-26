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

            METHOD_LIST_END
                // your declaration of processing function maybe like this:
                // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
                // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;

                void signup(drogon_model::augventure_db::User&& newUserData, std::function<void(const HttpResponsePtr&)>&& callback);
                void login(drogon_model::augventure_db::User&& loginUserData, std::function<void(const HttpResponsePtr&)>&& callback);

        };
    }
}
