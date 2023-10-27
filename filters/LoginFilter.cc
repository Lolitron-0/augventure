/**
 *
 *  LoginFilter.cc
 *
 */

#include "LoginFilter.h"
#include "utils/JWTService.h"

using namespace drogon;
using namespace augventure::filters;

void LoginFilter::doFilter(const HttpRequestPtr &req,
                         FilterCallback &&fcb,
                         FilterChainCallback &&fccb)
{
    const auto tokenOpt{ req->session()->getOptional<std::string>("session_token") };
    if (tokenOpt.has_value() && // have token
        JWTService::getUserIdFromJWT(tokenOpt.value()).has_value()) //token valid
    {
        //Passed
        fccb();
        return;
    }
    // Check failed
    auto res = drogon::HttpResponse::newHttpResponse();
    res->setStatusCode(k401Unauthorized);
    fcb(res);
}
