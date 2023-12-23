/**
 *
 *  LoginFilter.cc
 *
 */

#include "LoginFilter.h"
#include "plugins/JWTService.h"
#include <drogon/HttpAppFramework.h>

using namespace augventure::filters;
using namespace augventure::plugins;

void LoginFilter::doFilter(const HttpRequestPtr& req, FilterCallback&& fcb,
                           FilterChainCallback&& fccb)
{
    if (drogon::app()
            .getPlugin<JWTService>()
            ->getUserIdFromRequest(req)
            .has_value())
    {
        // Passed
        fccb();
        return;
    }
    // Check failed
    auto response = drogon::HttpResponse::newHttpResponse();
    response->setStatusCode(k401Unauthorized);
    response->setBody("not_logged_in");
    fcb(response);
}
