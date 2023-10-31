#pragma once
#include "Users.h"
#include <drogon/drogon.h>

namespace drogon_model
{
    namespace augventure_db
    {
        using User = Users;
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
}