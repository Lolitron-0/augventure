#pragma once
#include "Events.h"
#include "Models.h"
#include <drogon/drogon.h>
#include <drogon/orm/Criteria.h>
#include <string>

struct EventsFilteringData
{
    drogon::orm::Criteria criteria{};
    std::string columnToSortBy{
        drogon_model::augventure_db::Event::Cols::_creation_date
    };
    bool ascending{ false };
};

namespace drogon
{

template <> inline EventsFilteringData fromRequest(const HttpRequest& req)
{
using namespace drogon::orm;

    auto queryParams{ req.parameters() };
    if (queryParams.empty())
        return EventsFilteringData{};
    Criteria filteringCriteria{};
    CompareOperator op;
    for (auto param : queryParams)
    {
        if (param.second.empty() || drogon_model::augventure_db::Events::)
            continue;

        switch (param.second.at(0))
        {
        case '<':
            op = CompareOperator::LT;
            if (param.second.length() >= 2 && param.second.at(1) == '=')
                op = CompareOperator::LE;
            break;
        case '>':
            op = CompareOperator::GT;
            if (param.second.length() >= 2 && param.second.at(1) == '=')
                op = CompareOperator::GE;
            break;
        case '!':
            op = CompareOperator::NE;
            break;
        default:
            op = CompareOperator::EQ;
            break;
        }

		filteringCriteria = filteringCriteria && Criteria{param.first, op, param.second};
    }
}
} // namespace drogon
