/**
 *
 *  augventure_UserExistsFilter.cc
 *
 */

#include "augventure_UserExistsFilter.h"
#include "models/Users.h"
#include <drogon/orm/Mapper.h>
#include <drogon/drogon.h>

namespace augventure {
    namespace filters {

        void UserExistsFilter::doFilter(const HttpRequestPtr& req,
            FilterCallback&& fcb,
            FilterChainCallback&& fccb)
        {
            using namespace drogon_model::augventure_db;
            using namespace drogon::orm;

            auto dbClient{ drogon::app().getDbClient() };
            Mapper<User> mapper{ dbClient };

            User newUser{ drogon::fromRequest<User>(*req) };

            try
            {
                mapper.findFutureOne(
                    Criteria{ "email", CompareOperator::EQ, newUser.getValueOfEmail() } ||
                    Criteria{ "nickname", CompareOperator::EQ, newUser.getValueOfNickname() }).get();

                // failed
                Json::Value json;
                json["result"] = "error";
                json["why"] = "user already exists";
                auto res = drogon::HttpResponse::newHttpJsonResponse(json);
                fcb(res);
            }
            catch (const UnexpectedRows&) // no user found
            {
                // passed
                fccb();
                return;
            }
        }
    }
}
