#include "SprintsController.h"
#include "Models.h"
#include "utils/Macros.h"
#include <drogon/HttpResponse.h>
#include <drogon/HttpTypes.h>
#include <string>

void SprintsController::getOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Sprints::PrimaryKeyType&& id)
{
    SprintsControllerBase::getOne(req, std::move(callback), std::move(id));
}

void SprintsController::updateOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Sprints::PrimaryKeyType&& id)
{
    auto reqJson{ req->jsonObject() };
    if (reqJson)
        (*reqJson)[Sprints::Cols::_id] = id;

    SprintsControllerBase::updateOne(req, std::move(callback), std::move(id));
}

void SprintsController::deleteOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Sprints::PrimaryKeyType&& id)
{
    SprintsControllerBase::deleteOne(req, std::move(callback), std::move(id));
}

void SprintsController::get(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };
    SprintsControllerBase::get(
        req,
        [callbackPtr](const auto& resp)
        {
            if (resp->statusCode() != k200OK || resp->jsonObject()->empty())
            {
                (*callbackPtr)(resp);
                return;
            }
            expandSprintList(
                *resp->jsonObject(), [callbackPtr](const auto& jsonRes)
                { (*callbackPtr)(HttpResponse::newHttpJsonResponse(jsonRes)); },
                DB_EXCEPTION_HANDLER(*callbackPtr));
        });
}

void SprintsController::create(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    SprintsControllerBase::create(req, std::move(callback));
}
