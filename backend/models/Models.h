#pragma once
#include "Users.h"
#include "Events.h"
#include <drogon/drogon.h>

namespace drogon_model
{
    namespace augventure_db
    {
        using User = Users;
        using Event = Events;
    }
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

        //Json::StreamWriterBuilder wbuilder{};
        //std::string document = Json::writeString(wbuilder, *json);
        //LOG_TRACE << document;

        if (json)
        {
            return Event{ (*json)["event"] };
        }
        return Event{};
    }
}
