#include "AuthController.h"
#include "plugins/JWTService.h"
#include "plugins/SMTPMail.h"
#include "utils/Macros.h"
#include "utils/Utils.h"
#include <drogon/HttpResponse.h>
#include <drogon/HttpTypes.h>
#include <drogon/orm/Mapper.h>
#include <json/value.h>
#include <sodium.h>

namespace augventure
{
namespace controllers
{
void AuthController::signup(drogon_model::augventure_db::User&& newUserData,
                            drogon::AdviceCallback&& callback)
{
    using namespace drogon_model::augventure_db;
    using namespace drogon::orm;

    auto dbClient{ drogon::app().getDbClient() };
    Mapper<User> mapper{ dbClient };

    char hashed_password[crypto_pwhash_STRBYTES];
    if (crypto_pwhash_str(hashed_password,
                          newUserData.getValueOfPassword().c_str(),
                          newUserData.getValueOfPassword().length(),
                          crypto_pwhash_OPSLIMIT_MODERATE,
                          crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0)
    { // testing only
        std::cerr << "out of memory!\n";
    }

    // at this point newUserData is only an interface to retrieve input form
    // info
    newUserData.setPassword(hashed_password);

    auto auth_code = std::to_string(randombytes_uniform(1000000));
    auth_code =
        std::string(6ULL - std::min((std::size_t)6, auth_code.length()), '0') +
        auth_code;

    newUserData.setAuthCode(auth_code);

    auto* smtpmail = app().getPlugin<SMTPMail>();
    auto id = smtpmail->sendEmail("smtp.yandex.ru",       // The server IP/DNS
                                  587,                    // The port
                                  "augventure@yandex.ru", // Who send the email
                                  newUserData.getValueOfEmail(), // Send to whom
                                  "Auth code",            // Email Subject/Title
                                  auth_code,              // Content
                                  "augventure@yandex.ru", // Login user
                                  "rxjmbaazmwxzfttu",     // User password
                                  false                   // Is HTML content
    );

    auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };
    mapper.insert(
        newUserData,
        [=](User)
        {
            LOG_TRACE << "signup : ok";
            (*callbackPtr)(HttpResponse::newHttpResponse(k201Created, CT_NONE));
        },
        [=](const DrogonDbException& e)
        {
            LOG_TRACE << e.base().what();
            auto resp{ HttpResponse::newHttpResponse(k400BadRequest,
                                                     CT_TEXT_PLAIN) };
            resp->setBody("database exception: " +
                          (std::string)e.base().what());
            (*callbackPtr)(resp);
        });
}

void AuthController::login(const drogon::HttpRequestPtr& req,
                           drogon::AdviceCallback&& callback,
                           drogon_model::augventure_db::User&& loginUserData)
{
    using namespace drogon_model::augventure_db;
    using namespace drogon::orm;

    auto dbClient{ drogon::app().getDbClient() };
    Mapper<User> mapper{ dbClient };

    auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };

    mapper.findOne(
        Criteria{ User::Cols::_email, CompareOperator::EQ,
                  loginUserData.getValueOfEmail() },
        [=](User user)
        {
            auto response{ drogon::HttpResponse::newHttpJsonResponse(
                Json::Value{}) };
            if (crypto_pwhash_str_verify(
                    user.getValueOfPassword().c_str(),
                    loginUserData.getValueOfPassword().c_str(),
                    loginUserData.getValueOfPassword().length()) == 0)
            {
                auto token{ drogon::app()
                                .getPlugin<plugins::JWTService>()
                                ->generateFromUser(user) };
                response->setStatusCode(drogon::k202Accepted);
                (*response->jsonObject())["token"] = token;
                (*response->jsonObject())["user"] = user.toJson();
                augventure::utils::filterUserData(
                    (*response->jsonObject())["user"]);

                if (req->session()->find("session_token"))
                {
                    req->session()->modify<std::string>(
                        "session_token",
                        [token](std::string& oldToken) { oldToken = token; });
                }
                else
                {
                    req->session()->insert("session_token", token);
                }
                (*callbackPtr)(response);
            }
            else
            {
                SEND_RESPONSE(*callbackPtr, "wrong_password",
                              drogon::k401Unauthorized);
            }
        },
        [=](const DrogonDbException& e)
        {
            const UnexpectedRows* ur{ dynamic_cast<const UnexpectedRows*>(
                &e.base()) };
            auto resp{ drogon::HttpResponse::newHttpResponse() };
            resp->setContentTypeCode(CT_TEXT_PLAIN);
            if (ur)
            {
                LOG_INFO << "login : no_such_user";
                resp->setStatusCode(k401Unauthorized);
                resp->setBody("no_such_user");
                (*callbackPtr)(resp);
                return;
            }
            resp->setStatusCode(k400BadRequest);
            resp->setBody("database exception: " +
                          (std::string)e.base().what());
            (*callbackPtr)(resp);
        });
}

} // namespace controllers
} // namespace augventure
