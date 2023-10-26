#include "AuthController.h"
#include <drogon/orm/Mapper.h>
#include <sodium.h>
#include "utils/JWTService.h"


namespace augventure
{
    namespace controllers
    {
        void AuthController::signup(drogon_model::augventure_db::User&& newUserData, std::function<void(const HttpResponsePtr&)>&& callback)
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

            using cbType = std::function<void(const HttpResponsePtr&)>;
            auto callbackPtr{ std::make_shared<cbType>(std::forward<cbType>(callback)) };
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

        void AuthController::login(drogon_model::augventure_db::User&& loginUserData, std::function<void(const HttpResponsePtr&)>&& callback)
        {
            using namespace drogon_model::augventure_db;
            using namespace drogon::orm;

            auto dbClient{ drogon::app().getDbClient() };
            Mapper<User> mapper{ dbClient };

            using cbType = std::function<void(const HttpResponsePtr&)>;
            auto callbackPtr{ std::make_shared<cbType>(std::forward<cbType>(callback)) };

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

    }
}