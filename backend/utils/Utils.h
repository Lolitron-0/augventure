#pragma once
#include <drogon/drogon.h>
#include <drogon/drogon_callbacks.h>
#include <drogon/orm/Exception.h>
#include <json/value.h>
#include <string>
#include <string_view>

namespace augventure
{

namespace utils
{

std::string getMediaTypeString(const std::string_view& extension);

std::string getUniqueFileName(const std::string_view& fileName);

void filterUserData(Json::Value& userData);

inline void handleDatabaseException(const drogon::orm::DrogonDbException& e,
                                    const drogon::AdviceCallback& callback)
{

    LOG_TRACE << e.base().what();
    auto resp{ drogon::HttpResponse::newHttpResponse(drogon::k400BadRequest,
                                                     drogon::CT_TEXT_PLAIN) };
    resp->setBody("database exception: " + (std::string)e.base().what());
    callback(resp);
}

} // namespace utils
} // namespace augventure
