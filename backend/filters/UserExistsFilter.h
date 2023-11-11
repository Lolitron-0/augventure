/**
 *
 *  augventure_UserExistsFilter.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;
namespace augventure {
    namespace filters {

        class UserExistsFilter : public HttpFilter<UserExistsFilter>
        {
        public:
            UserExistsFilter() {}
            void doFilter(const HttpRequestPtr& req,
                FilterCallback&& fcb,
                FilterChainCallback&& fccb) override;
        };

    }
}
