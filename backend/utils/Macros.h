#pragma once
#define MAKE_CALLBACK_HEAP_PTR(callbackName) std::make_shared<drogon::AdviceCallback>(std::forward<drogon::AdviceCallback>(callbackName))

#define CURRENT_USER_ID(requestName) drogon::app().getPlugin<augventure::plugins::JWTService>()->getUserIdFromRequest(requestName).value()