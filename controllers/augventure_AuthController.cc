#include "augventure_AuthController.h"
#include <drogon/orm/Mapper.h>
#include <sodium.h>


namespace augventure
{
    namespace controllers
    {
        void AuthController::signUp(drogon_model::augventure_db::User&& newUser, std::function<void(const HttpResponsePtr&)>&& callback)
        {
            using namespace drogon_model::augventure_db;
            auto dbClient{ drogon::app().getDbClient() };
            drogon::orm::Mapper<User> mapper{ dbClient };

            char hashed_password[crypto_pwhash_STRBYTES];
            if (crypto_pwhash_str(hashed_password, newUser.getValueOfPasswordHash().c_str(), newUser.getValueOfPasswordHash().length(),
                crypto_pwhash_OPSLIMIT_MODERATE, crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) { //testing only
                std::cerr << "out of memory!\n";
            }
            newUser.setPasswordHash(hashed_password);
            
            mapper.insert(newUser);

            Json::Value respJson;
            respJson["result"] = "ok";
            callback(HttpResponse::newHttpJsonResponse(respJson));
        }
    }
}