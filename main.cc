#include <drogon/drogon.h>
#include <drogon/orm/Mapper.h>
#include <models/Test.h>
#include <sodium.h>

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

    if (sodium_init() < 0)
    {
        std::cerr << "Failed to load sodium!";
        abort();
    }

    std::string pass = "123456";
    char hashed_password[crypto_pwhash_STRBYTES];

    if (crypto_pwhash_str
    (hashed_password, pass.c_str(), pass.length(),
        crypto_pwhash_OPSLIMIT_MODERATE, crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) { //testing only
        std::cerr << "out of memory!\n";
    }
    std::cout << hashed_password << '\n';

    if (crypto_pwhash_str_verify(hashed_password, "123456", 6) != 0)
    {
        std::cout << "wrong\n";
    }
    else
    {
        std::cout << "correct\n";
    }

    //Set HTTP listener address and port
    drogon::app().addListener("0.0.0.0", 80);
    //Load config file
    drogon::app().loadConfigFile("../config.json");
    //drogon::app().loadConfigFile("../config.yaml");
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}