#include "AuthController.h"
#include <drogon/orm/Mapper.h>
#include <sodium.h>
#include "plugins/JWTService.h"
#include "plugins/SMTPMail.h"
#include "utils/Macros.h"

namespace augventure
{
    namespace controllers
    {
        void AuthController::signup(drogon_model::augventure_db::User&& newUserData, drogon::AdviceCallback&& callback)
        {
            using namespace drogon_model::augventure_db;
            using namespace drogon::orm;

            auto dbClient{ drogon::app().getDbClient() };
            Mapper<User> mapper{ dbClient };

            char hashed_password[crypto_pwhash_STRBYTES];
            if (crypto_pwhash_str(hashed_password, newUserData.getValueOfPasswordHash().c_str(), newUserData.getValueOfPasswordHash().length(),
                crypto_pwhash_OPSLIMIT_MODERATE, crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) { //testing only
                std::cerr << "out of memory!\n";
            }

            // at this point newUserData is only an interface to retrieve input form info
            newUserData.setPasswordHash(hashed_password);


            auto auth_code = std::to_string(randombytes_uniform(1000000));
            auth_code = std::string(6ULL - std::min((std::size_t)6, auth_code.length()), '0') + auth_code;

            newUserData.setAuthCode(auth_code);

            auto* smtpmail = app().getPlugin<SMTPMail>();
            auto id = smtpmail->sendEmail(
                "smtp.yandex.ru",              // The server IP/DNS
                587,                           // The port
                "augventure@yandex.ru",        // Who send the email
                newUserData.getValueOfEmail(), // Send to whom
                "Auth code",                   // Email Subject/Title
                auth_code,                     // Content
                "augventure@yandex.ru",        // Login user
                "rxjmbaazmwxzfttu",            // User password
                false                          // Is HTML content
            );

            auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };
            mapper.insert(newUserData,
                [=](User)
                {
                    Json::Value respJson;
                    respJson["result"] = "ok";
                    (*callbackPtr)(HttpResponse::newHttpJsonResponse(respJson));
                },
                [=](const DrogonDbException& e)
                {
                    LOG_TRACE << e.base().what();
                    auto resp{ HttpResponse::newHttpResponse() };
                    resp->setStatusCode(k400BadRequest);
                    (*callbackPtr)(resp);
                });


        }

        void AuthController::login(const drogon::HttpRequestPtr& req, drogon::AdviceCallback&& callback,
            drogon_model::augventure_db::User&& loginUserData)
        {
            using namespace drogon_model::augventure_db;
            using namespace drogon::orm;

            auto dbClient{ drogon::app().getDbClient() };
            Mapper<User> mapper{ dbClient };

            auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };

            mapper.findOne(
                Criteria{ User::Cols::_email, CompareOperator::EQ, loginUserData.getValueOfEmail() },
                [=](User user)
                {
                    Json::Value json;
                    if (crypto_pwhash_str_verify(
                        user.getValueOfPasswordHash().c_str(),
                        loginUserData.getValueOfPasswordHash().c_str(),
                        loginUserData.getValueOfPasswordHash().length()) == 0)
                    {
                        auto token = drogon::app().getPlugin<plugins::JWTService>()->generateFromUser(user);
                        json["result"] = "ok";
                        json["token"] = token;
                        if (req->session()->find("session_token"))
                        {
                            req->session()->modify<std::string>("session_token", [token](std::string& oldToken)
                                {
                                    oldToken = token;
                                });
                        }
                        else
                        {
                            req->session()->insert("session_token", token);
                        }
                    }
                    else
                    {
                        json["result"] = "wrong_password";
                    }
                    (*callbackPtr)(drogon::HttpResponse::newHttpJsonResponse(json));
                },
                [=](const DrogonDbException& e)
                {
                    const UnexpectedRows* ur = dynamic_cast<const UnexpectedRows*>(&e.base());
                    if (ur)
                    {
                        Json::Value json;
                        json["result"] = "no_such_user";
                        (*callbackPtr)(drogon::HttpResponse::newHttpJsonResponse(json));
                    }
                    auto resp = drogon::HttpResponse::newHttpResponse();
                    resp->setStatusCode(k400BadRequest);
                    (*callbackPtr)(resp);
                }
            );
        }

        void AuthController::currentUserTest(const drogon::HttpRequestPtr& req, drogon::AdviceCallback&& callback)
        {
            using namespace drogon_model::augventure_db;
            using namespace drogon::orm;

            auto dbClient{ drogon::app().getDbClient() };
            Mapper<User> mapper{ dbClient };

            auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };
            auto currentUserId{ CURRENT_USER_ID(req) }; // filter guarantees result
            mapper.findByPrimaryKey(currentUserId, [=](User currentUser)
                {
                    Json::Value respJson;
                    respJson["result"] = "ok";
                    respJson["user"] = currentUser.toJson();
                    (*callbackPtr)(drogon::HttpResponse::newHttpJsonResponse(respJson));
                },
                [=](const DrogonDbException& e)
                {
                    auto resp = drogon::HttpResponse::newHttpResponse();
                    resp->setStatusCode(k400BadRequest);
                    (*callbackPtr)(resp);
                });

        }

        void AuthController::passwordReset(const drogon::HttpRequestPtr& req, drogon::AdviceCallback&& callback)
        {
            using namespace drogon_model::augventure_db;
            using namespace drogon::orm;

            auto dbClient{ drogon::app().getDbClient() };
            Mapper<User> mapper{ dbClient };


            auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };
            auto currentUserId{ CURRENT_USER_ID(req) }; // filter guarantees result

            mapper.findByPrimaryKey(currentUserId, [=](User currentUser)
                {
                    Json::Value jsonPasswords{ *(req->getJsonObject()) };

                    std::string oldPassword = jsonPasswords["old_password"].asString();

                    if (crypto_pwhash_str_verify(
                        currentUser.getValueOfPasswordHash().c_str(),
                        oldPassword.c_str(),
                        oldPassword.length()) == 0)
                    {
                        std::string newPassword = jsonPasswords["new_password"].asString();
                        char hashedNewPassword[crypto_pwhash_STRBYTES];
                        if (crypto_pwhash_str(hashedNewPassword, newPassword.c_str(), newPassword.length(),
                            crypto_pwhash_OPSLIMIT_MODERATE, crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) { //testing only
                            std::cerr << "out of memory!\n";
                        }
                        currentUser.setPasswordHash(hashedNewPassword);

                        Mapper<User> updateMapper{ dbClient };
                        updateMapper.update(currentUser,
                            [=](size_t)
                            {
                                Json::Value respJson;
                                respJson["result"] = "ok";
                                (*callbackPtr)(HttpResponse::newHttpJsonResponse(respJson));
                            },
                            [=](const DrogonDbException& e)
                            {
                                LOG_TRACE << e.base().what();
                                auto resp{ HttpResponse::newHttpResponse() };
                                resp->setStatusCode(k400BadRequest);
                                (*callbackPtr)(resp);
                            });
                    }
                    else
                    {
                        Json::Value respJson;
                        respJson["result"] = "wrong_old_password";
                        (*callbackPtr)(drogon::HttpResponse::newHttpJsonResponse(respJson));
                    }
                },
                [=](const DrogonDbException& e)
                {
                    auto resp = drogon::HttpResponse::newHttpResponse();
                    resp->setStatusCode(k400BadRequest);
                    (*callbackPtr)(resp);
                });

        }

    }
}
