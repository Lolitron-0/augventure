#include <drogon/drogon.h>
#include <drogon/orm/Mapper.h>
#include <sodium.h>

int main() {
    if (sodium_init() < 0)
    {
        std::cerr << "Failed to load sodium!";
        abort();
    } 

    drogon::HttpAppFramework::instance().registerHandler("/", [](const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback) {
            callback(drogon::HttpResponse::newHttpViewResponse("test.csp"));
        });

    drogon::HttpAppFramework::instance().registerHandler("/password_reset", [](const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback) {
            callback(drogon::HttpResponse::newHttpViewResponse("PasswordReset.csp"));
        }, {drogon::Get});
    
    //Set HTTP listener address and port
    drogon::app().addListener("0.0.0.0", 80);
    //Load config file
    drogon::app().loadConfigFile("../config.json");
    //drogon::app().loadConfigFile("../config.yaml");
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}
