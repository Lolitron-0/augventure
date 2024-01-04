/**
 *
 *  PathOwnershipFilter.cc
 *
 */

#include "PathOwnershipFilter.h"

using namespace drogon;
using namespace augventure::filters;

void PathOwnershipFilter::doFilter(const HttpRequestPtr& req,
                                   FilterCallback&& fcb,
                                   FilterChainCallback&& fccb)
{
    // Edit your logic here
    if (1)
    {
        // Passed
        fccb();
        return;
    }
    // Check failed
    auto res = drogon::HttpResponse::newHttpResponse();
    res->setStatusCode(k500InternalServerError);
    fcb(res);
}
