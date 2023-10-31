/**
 *
 *  augventure_UserExistsFilter.cc
 *
 */

#include "UserExistsFilter.h"
#include "models/User.h"
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
                    Criteria{ User::Cols::_email, CompareOperator::EQ, newUser.getValueOfEmail() } ||
                    Criteria{ User::Cols::_nickname, CompareOperator::EQ, newUser.getValueOfNickname() }).get();

                // failed
                Json::Value json;
                json["result"] = "already_exists";
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
