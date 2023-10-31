#include "AuthController.h"
#include <drogon/orm/Mapper.h>
#include <sodium.h>
#include "utils/JWTService.h"


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

            auto callbackPtr{ std::make_shared<drogon::AdviceCallback>(std::forward<drogon::AdviceCallback>(callback)) };
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

            auto callbackPtr{ std::make_shared<drogon::AdviceCallback>(std::forward<drogon::AdviceCallback>(callback)) };

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
                        auto token = JWTService::generateFromUser(user);
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
                        // no such user
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

            auto callbackPtr{ std::make_shared<drogon::AdviceCallback>(std::forward<drogon::AdviceCallback>(callback)) };
            auto currentUserId{ JWTService::getUserIdFromJWT(req->session()->get<std::string>("session_token")).value()}; // filter guarantees result
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


            auto callbackPtr{ std::make_shared<drogon::AdviceCallback>(std::forward<drogon::AdviceCallback>(callback)) };
            auto currentUserId{ JWTService::getUserIdFromJWT(req->session()->get<std::string>("session_token")).value() }; // filter guarantees result

            mapper.findByPrimaryKey(currentUserId, [=](User currentUser)
                {
                    Json::Value jsonPasswords { *(req->getJsonObject()) };

                    char hashedOldPassword[crypto_pwhash_STRBYTES];
                    std::string oldPassword = jsonPasswords["old_password"].asString();
                    if (crypto_pwhash_str(hashedOldPassword, oldPassword.c_str(), oldPassword.length(),
                        crypto_pwhash_OPSLIMIT_MODERATE, crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) { //testing only
                        std::cerr << "out of memory!\n";
                    }
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

                        Mapper<User> resetMapper{ dbClient };
                        resetMapper.update(currentUser,
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