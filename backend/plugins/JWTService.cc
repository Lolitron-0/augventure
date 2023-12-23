#include "JWTService.h"
#include "jwt-cpp/jwt.h"
#include <drogon/HttpRequest.h>
#include <exception>
#include <optional>
#include <trantor/utils/Logger.h>

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
    try
    {
        auto decoded{ jwt::decode(token) };
        m_VerifierPtr->verify(decoded);
        return stoi(decoded.get_payload_claim("user").as_string());
    }
    catch (const std::exception& e)
    {
        LOG_DEBUG << e.what();
        return std::nullopt;
    }
}

std::optional<std::string>
JWTService::getJWTFromRequest(const drogon::HttpRequestPtr& req) const
{
    if (req->session()->getOptional<std::string>("session_token").has_value())
    {
		LOG_TRACE << "Got token from cookies";
        return req->session()->getOptional<std::string>("session_token");
    }
    else if (req->headers().find("authorization") != req->headers().end())
    {
		LOG_TRACE << "Got token from headers";
        return req->headers().at("authorization");
    }
    return std::nullopt;
}

std::optional<int>
JWTService::getUserIdFromRequest(const drogon::HttpRequestPtr& req) const
{
    return getUserIdFromJWT(getJWTFromRequest(req).value_or(""));
}

void JWTService::shutdown() {}
} // namespace plugins
} // namespace augventure
