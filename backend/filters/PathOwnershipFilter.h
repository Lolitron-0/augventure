/**
 *
 *  PathOwnershipFilter.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;
namespace augventure
{
namespace filters
{

class PathOwnershipFilter : public HttpFilter<PathOwnershipFilter>
{
public:
    PathOwnershipFilter() {}
    void doFilter(const HttpRequestPtr& req, FilterCallback&& fcb,
                  FilterChainCallback&& fccb) override;
};

} // namespace filters
} // namespace augventure
