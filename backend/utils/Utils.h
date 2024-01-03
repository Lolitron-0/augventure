#pragma once
#include <drogon/drogon.h>
#include <drogon/drogon_callbacks.h>
#include <drogon/orm/Exception.h>
#include <string>

inline void handleDatabaseException(const drogon::orm::DrogonDbException& e,
                                    const drogon::AdviceCallback& callback)
{

    LOG_TRACE << e.base().what();
    auto resp{ drogon::HttpResponse::newHttpResponse(drogon::k400BadRequest,
                                                     drogon::CT_TEXT_PLAIN) };
    resp->setBody("database exception: " + (std::string)e.base().what());
    callback(resp);
}
