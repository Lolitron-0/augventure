#include "JWTService.h"
#include "openssl/hmac.h"

namespace augventure
{

    const std::string JWTService::s_Secret{ drogon::app().getCustomConfig()["jwt-secret"].asString() };
    const int JWTService::s_SessionDuration{ drogon::app().getCustomConfig()["jwt-sessionDuration"].asInt() };
    const jwt::verifier<jwt::default_clock, jwt::traits::kazuho_picojson> JWTService::s_Verifier{
        jwt::verify()
        .allow_algorithm(jwt::algorithm::hs256{JWTService::s_Secret})
        .with_issuer("auth0") };


    std::string JWTService::generateFromUser(const drogon_model::augventure_db::User& user)
    {
        return jwt::create()
            .set_issuer("auth0")
            .set_type("JWS")
            .set_issued_at(std::chrono::system_clock::now())
            .set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds{ s_SessionDuration })
            .set_payload_claim("user", jwt::claim{ std::to_string(user.getValueOfId()) })
            .sign(jwt::algorithm::hs256{s_Secret});
    }

    std::optional<int> JWTService::getUserIdFromJWT(const std::string& token)
    {
        auto decoded = jwt::decode(token);
        try
        {
            s_Verifier.verify(decoded);
        }
        catch (const std::runtime_error& e)
        {
            LOG_TRACE << e.what();
            return std::nullopt;
        }
        return decoded.get_payload_claim("user").as_integer();
    }

}