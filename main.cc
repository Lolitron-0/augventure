#include <drogon/drogon.h>
#include <drogon/orm/Mapper.h>
#include <models/Test.h>
#include <bcrypt/bcrypt.h>

int main() {
    drogon::HttpAppFramework::instance().registerHandler("/", [](const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback)
        {
            static int count = 0;

            auto dbClientPtr = drogon::app().getDbClient();
            drogon::orm::Mapper<drogon_model::testdb::Test> mapper{ dbClientPtr };


            auto result = mapper.findFutureAll().get();
            Json::Value json, objJson;
            json["objects"] = {};
            for (const auto& obj : result)
            {
                objJson["name"] = obj.getValueOfName();
                objJson["number"] = obj.getValueOfNumber();
                json["objects"].append(objJson);
            }

            callback(drogon::HttpResponse::newHttpJsonResponse(json));
        });

    char salt[BCRYPT_HASHSIZE];
    char hash[BCRYPT_HASHSIZE];
    bcrypt_gensalt(12, salt);
    bcrypt_hashpw("12345", salt, hash);
    std::cout << hash << '\n';

    //Set HTTP listener address and port
    drogon::app().addListener("0.0.0.0",80);
    //Load config file
    drogon::app().loadConfigFile("../config.json");
    //drogon::app().loadConfigFile("../config.yaml");
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}
