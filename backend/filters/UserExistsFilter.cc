/**
 *
 *  augventure_UserExistsFilter.cc
 *
 */

#include "UserExistsFilter.h"
#include "models/Models.h"
#include <drogon/HttpTypes.h>
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
                    Criteria{ User::Cols::_username, CompareOperator::EQ, newUser.getValueOfUsername() }).get();

                // failed
				LOG_TRACE << "UserExistsFilter : fail";
                auto resp = drogon::HttpResponse::newHttpResponse(drogon::k401Unauthorized, drogon::CT_TEXT_PLAIN);
				resp->setBody("already_exists");
                fcb(resp);
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
