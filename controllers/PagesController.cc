#include "PagesController.h"

namespace augventure
{
    namespace controllers
    {

        void PagesController::loginSignup(const drogon::HttpRequestPtr& req, drogon::AdviceCallback&& callback)
        {
            callback(drogon::HttpResponse::newHttpViewResponse("test.csp"));
        }

        void PagesController::passwordReset(const drogon::HttpRequestPtr& req, drogon::AdviceCallback&& callback)
        {
            callback(drogon::HttpResponse::newHttpViewResponse("password_reset.csp"));
        }

        void PagesController::createEvent(const drogon::HttpRequestPtr& req, drogon::AdviceCallback&& callback)
        {
            callback(drogon::HttpResponse::newHttpViewResponse("create_event.csp"));
        }
    }

}