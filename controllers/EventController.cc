#include "EventController.h"
#include "plugins/JWTService.h"
#include "utils/Macros.h"

namespace augventure
{
    namespace controllers
    {
        // Add definition of your processing function here

        void EventController::createEvent(const drogon::HttpRequestPtr& req, drogon::AdviceCallback&& callback,
            drogon_model::augventure_db::Event&& newEventData)
        {
            using namespace drogon_model::augventure_db;
            using namespace drogon::orm;

            auto dbClient{ drogon::app().getDbClient() };
            Mapper<Event> mapper{ dbClient };
            auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };
            auto currentUserId{ CURRENT_USER_ID(req) };

            newEventData.setAuthorId(currentUserId);
            mapper.insert(newEventData, 
                [=](Event) 
                {
                    Json::Value respJson;
                    respJson["result"] = "ok";
                    (*callbackPtr)(drogon::HttpResponse::newHttpJsonResponse(respJson));
                }, 
                [=](const DrogonDbException& e) 
                {
                    LOG_TRACE << e.base().what();
                    auto resp{ HttpResponse::newHttpResponse() };
                    resp->setStatusCode(k400BadRequest);
                    (*callbackPtr)(resp);
                });
        }

    }
}