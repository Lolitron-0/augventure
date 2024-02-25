#pragma once
#pragma once

#include "models/Models.h"
#include <drogon/HttpController.h>

using namespace drogon;

namespace augventure
{
struct UserSignUpInfo;

namespace controllers
{
class AuthController : public drogon::HttpController<AuthController>
{
public:
    METHOD_LIST_BEGIN

    ADD_METHOD_TO(AuthController::signup, "api/auth/signup", Post,
                  "augventure::filters::UserExistsFilter");
    ADD_METHOD_TO(AuthController::login, "api/auth/login", Post);

    METHOD_LIST_END

    void signup(drogon_model::augventure_db::User&& newUserData,
                drogon::AdviceCallback&& callback);
    void login(const drogon::HttpRequestPtr& req,
               drogon::AdviceCallback&& callback,
               drogon_model::augventure_db::User&& loginUserData);
};
} // namespace controllers
} // namespace augventure
