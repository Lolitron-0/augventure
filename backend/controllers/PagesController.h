#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace augventure
{
namespace controllers
{
class PagesController : public drogon::HttpController<PagesController>
{
  public:
      METHOD_LIST_BEGIN
          ADD_METHOD_TO(PagesController::loginSignup, "/", Get);
          ADD_METHOD_TO(PagesController::passwordReset, "/password_reset", Get);
          ADD_METHOD_TO(PagesController::createEvent, "/events/create", Get);
      METHOD_LIST_END
          void loginSignup(const drogon::HttpRequestPtr& req, drogon::AdviceCallback&& callback);
          void passwordReset(const drogon::HttpRequestPtr& req, drogon::AdviceCallback&& callback);
          void createEvent(const drogon::HttpRequestPtr& req, drogon::AdviceCallback&& callback);
};
}
}
