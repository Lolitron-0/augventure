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
        // should be called after config loading
        static void init();

        static std::string generateFromUser(const drogon_model::augventure_db::User& user);
        static std::optional<int> getUserIdFromJWT(const std::string& token);
    private:
        static std::string s_Secret;
        static int s_SessionDuration;
        using JWTVerifier = jwt::verifier<jwt::default_clock, jwt::traits::kazuho_picojson>;
        static std::unique_ptr<JWTVerifier> s_VerifierPtr;
    };
}