#pragma once

#include "models/Models.h"
#include <drogon/drogon.h>
#undef min
#undef max
#include <jwt-cpp/jwt.h>

namespace augventure
{
namespace plugins
{
class JWTService : public drogon::Plugin<JWTService>
{
public:
    void initAndStart(const Json::Value& config) override;

    std::string
    generateFromUser(const drogon_model::augventure_db::User& user) const;
    std::optional<int> getUserIdFromJWT(const std::string& token) const;
    std::optional<int>
    getUserIdFromRequest(const drogon::HttpRequestPtr&) const;

    void shutdown() override;

private:
    std::string m_Secret;
    int m_SessionDuration;
    using JWTVerifier =
        jwt::verifier<jwt::default_clock, jwt::traits::kazuho_picojson>;
    std::unique_ptr<JWTVerifier> m_VerifierPtr;
};
} // namespace plugins
} // namespace augventure
