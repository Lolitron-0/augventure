#pragma once
#define MAKE_CALLBACK_HEAP_PTR(callbackName)                                   \
    std::make_shared<drogon::AdviceCallback>(                                  \
        std::forward<drogon::AdviceCallback>(callbackName))

#define CURRENT_USER_ID(requestObj)                                            \
    drogon::app()                                                              \
        .getPlugin<::augventure::plugins::JWTService>()                        \
        ->getUserIdFromRequest(requestObj)                                     \
        .value()

#define HANDLE_DB_EXCEPTION(callback)                                          \
    [callbackCapture = (callback)](auto e)                                     \
    { handleDatabaseException(e, callbackCapture); }
