#pragma once
#include "Events.h"
#include "Sprints.h"
#include "Posts.h"
#include "Users.h"
#include <drogon/HttpRequest.h>
#include <drogon/drogon.h>
#include <drogon/orm/Criteria.h>
#include <json/value.h>
#include <string>
#include <vector>

namespace drogon_model
{
namespace augventure_db
{
using User = Users;
using Event = Events;
using Sprint = Sprints;
} // namespace augventure_db
} // namespace drogon_model

using PrimaryKeyType = drogon_model::augventure_db::User::PrimaryKeyType;

inline trantor::Date dateFromJsonString(const std::string& string)
{
    struct tm stm;
    memset(&stm, 0, sizeof(stm));
    const char* p = strptime(string.c_str(), "%Y-%m-%d %H:%M:%S", &stm);
    time_t t = mktime(&stm);
    return trantor::Date{ (int64_t)(t * 1000000) };
}

namespace drogon
{


template <>
inline drogon_model::augventure_db::User fromRequest(const HttpRequest& req)
{
    using namespace drogon_model::augventure_db;

    auto json{ req.getJsonObject() };

    if (json)
    {
        return User{ (*json)["user"] };
    }
    return User{};
}

template <>
inline drogon_model::augventure_db::Event fromRequest(const HttpRequest& req)
{
    using namespace drogon_model::augventure_db;

    auto json{ req.getJsonObject() };

    // Json::StreamWriterBuilder wbuilder{};
    // std::string document = Json::writeString(wbuilder, *json);
    // LOG_TRACE << document;

    if (json)
    {
        return Event{ (*json)["event"] };
    }
    return Event{};
}
} // namespace drogon
