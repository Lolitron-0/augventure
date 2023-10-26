#pragma once

#include "models/Users.h"
#include <drogon/drogon.h>
#undef min
#undef max
#include <jwt-cpp/jwt.h>

namespace augventure
{

    struct JsonCppTraits;

    class JWTService
    {
    public:
        static std::string generateFromUser(const drogon_model::augventure_db::User& user);
        static std::optional<int> getUserIdFromJWT(const std::string& token);
    private:
        static const std::string s_Secret;
        static const int s_SessionDuration;
        static const jwt::verifier<jwt::default_clock, jwt::traits::kazuho_picojson> s_Verifier;
    };
}