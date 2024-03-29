#pragma once
#include "Events.h"
#include "Posts.h"
#include "PostMedia.h"
#include "Sprints.h"
#include "Users.h"
#include "Votes.h"
#include <cstdint>
#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>
#include <drogon/drogon.h>
#include <drogon/drogon_callbacks.h>
#include <drogon/orm/Criteria.h>
#include <drogon/orm/Exception.h>
#include <functional>
#include <json/value.h>
#include <string>
#include <utility>
#include <vector>

namespace drogon_model
{
namespace augventure_db
{
using User = Users;
using Event = Events;
using Sprint = Sprints;
using Suggestion = Suggestions;
using Vote = Votes;
} // namespace augventure_db
} // namespace drogon_model

using PrimaryKeyType = drogon_model::augventure_db::User::PrimaryKeyType;

void getFullEventData(
    const Json::Value& eventJson,
    std::function<void(const Json::Value& result)>&& successCallback,
    drogon::orm::DrogonDbExceptionCallback&& dbExceptionCallback);

void expandEventList(
    const Json::Value& eventListJson,
    std::function<void(const Json::Value& result)>&& successCallback,
    drogon::orm::DrogonDbExceptionCallback&& dbExceptionCallback);

void expandSprintList(const Json::Value& sprintListJson,
    std::function<void(const Json::Value& result)>&& successCallback,
    drogon::orm::DrogonDbExceptionCallback&& dbExceptionCallback);

void expandSuggestionList(
    const Json::Value& suggestionListJson, int8_t voteSort,
    std::function<void(const Json::Value& result)>&& successCallback,
    drogon::orm::DrogonDbExceptionCallback&& dbExceptionCallback);

void createSeveralPostMedia(
    const std::vector<Json::Value>& jsons, uint32_t n,
    std::function<void(void)>&& successCallback,
    drogon::orm::DrogonDbExceptionCallback&& dbExceptionCallback);

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
