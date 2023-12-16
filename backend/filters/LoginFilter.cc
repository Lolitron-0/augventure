/**
 *
 *  LoginFilter.cc
 *
 */

#include "LoginFilter.h"
#include "plugins/JWTService.h"

using namespace drogon;
using namespace augventure::filters;
using namespace augventure::plugins;

void LoginFilter::doFilter(const HttpRequestPtr &req,
                         FilterCallback &&fcb,
                         FilterChainCallback &&fccb)
{
    const auto tokenOpt{ req->session()->getOptional<std::string>("session_token") };
    if (tokenOpt.has_value() && // have token
        app().getPlugin<JWTService>()->getUserIdFromJWT(tokenOpt.value()).has_value()) //token valid
    {
        //Passed
        fccb();
        return;
    }
    // Check failed
    auto response = drogon::HttpResponse::newHttpResponse();
    response->setStatusCode(k401Unauthorized);
	response->setBody("not_logged_in");
    fcb(response);
}
