#pragma once
#include "plugins/JWTService.h"
#include "utils/Utils.h"

#define MAKE_CALLBACK_HEAP_PTR(callbackName)                                   \
    std::make_shared<drogon::AdviceCallback>(                                  \
        std::forward<drogon::AdviceCallback>(callbackName))

#define CURRENT_USER_ID(requestObj)                                            \
    drogon::app()                                                              \
        .getPlugin<::augventure::plugins::JWTService>()                        \
        ->getUserIdFromRequest(requestObj)                                     \
        .value()

#define DB_EXCEPTION_HANDLER(callback)                                         \
    [callbackCapture = (callback)](auto&& e)                                   \
    { ::augventure::utils::handleDatabaseException(e, callbackCapture); }

#define INTERNAL_GET_MACRO(_1, _2, _3, NAME, ...) NAME
#define INTERNAL_SEND_RESPONSE_WITH_CODE(callbackObj, message, code)           \
    do                                                                         \
    {                                                                          \
        auto resp{ HttpResponse::newHttpResponse(code,                         \
                                                 drogon::CT_TEXT_PLAIN) };     \
        resp->setBody((message));                                              \
        (callbackObj)(resp);                                                   \
        return;                                                                \
    } while (0);
#define INTERNAL_SEND_RESPONSE_NO_CODE(callbackObj, message)                   \
    INTERNAL_SEND_RESPONSE_WITH_CODE(callbackObj, message, drogon::k200OK)

#define INTERNAL_EXPAND(x) x

/// callback, message, code
#define SEND_RESPONSE(...)                                                     \
    INTERNAL_EXPAND(INTERNAL_GET_MACRO(__VA_ARGS__,                             \
                                      INTERNAL_SEND_RESPONSE_WITH_CODE,          \
                       INTERNAL_SEND_RESPONSE_NO_CODE)                         \
    (__VA_ARGS__))
