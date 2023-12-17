#include "JWTService.h"

namespace augventure
{
namespace plugins
{
void JWTService::initAndStart(const Json::Value& config)
{
    m_Secret = drogon::app().getCustomConfig()["jwt-secret"].asString();
    m_SessionDuration =
        drogon::app().getCustomConfig()["jwt-sessionDuration"].asInt();
    m_VerifierPtr = std::make_unique<JWTVerifier>(
        jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{ JWTService::m_Secret })
            .with_issuer("auth0"));
    LOG_INFO << "JWTService: successfully loaded and started";
}

std::string JWTService::generateFromUser(
    const drogon_model::augventure_db::User& user) const
{
    return jwt::create()
        .set_issuer("auth0")
        .set_type("JWS")
        .set_issued_at(std::chrono::system_clock::now())
        .set_expires_at(std::chrono::system_clock::now() +
                        std::chrono::seconds{ m_SessionDuration })
        .set_payload_claim("user",
                           jwt::claim{ std::to_string(user.getValueOfId()) })
        .sign(jwt::algorithm::hs256{ m_Secret });
}

std::optional<int> JWTService::getUserIdFromJWT(const std::string& token) const
{
    auto decoded = jwt::decode(token);
    try
    {
        m_VerifierPtr->verify(decoded);
    }
    catch (const std::runtime_error& e)
    {
        LOG_TRACE << e.what();
        return std::nullopt;
    }
    return stoi(decoded.get_payload_claim("user").as_string());
}

std::optional<int>
JWTService::getUserIdFromRequest(const drogon::HttpRequestPtr& req) const
{
    return getUserIdFromJWT(req->session()->get<std::string>("session_token"));
}

void JWTService::shutdown() {}
} // namespace plugins
} // namespace augventure
