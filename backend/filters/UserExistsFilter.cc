/**
 *
 *  augventure_UserExistsFilter.cc
 *
 */

#include "UserExistsFilter.h"
#include "models/Models.h"
#include "utils/Macros.h"
#include <drogon/HttpTypes.h>
#include <drogon/drogon.h>
#include <drogon/orm/Mapper.h>

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

            User newUser{drogon::fromRequest<User>(*req)};

            mapper.findOne(
                Criteria{User::Cols::_email, CompareOperator::EQ, newUser.getValueOfEmail()}
                    || Criteria{User::Cols::_username,
                                CompareOperator::EQ,
                                newUser.getValueOfUsername()},
                [fcb](auto)
                {
                    // failed
                    LOG_TRACE << "UserExistsFilter : fail";
                    auto resp = drogon::HttpResponse::newHttpResponse(drogon::k401Unauthorized,
                                                                      drogon::CT_TEXT_PLAIN);
                    resp->setBody("already_exists");
                    fcb(resp);
                },
                [fccb, fcb](const DrogonDbException &e)
                {
                    const auto *ur{dynamic_cast<const UnexpectedRows *>(&e.base())};
                    if (ur) // no user found
                    {
                        fccb();
                        return;
                    }
                    std::invoke(DB_EXCEPTION_HANDLER(fcb), e);
                });
        }
    }
}
