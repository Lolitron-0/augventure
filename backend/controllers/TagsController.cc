#include "TagsController.h"
#include <string>

void TagsController::getOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Tags::PrimaryKeyType&& id)
{
    TagsControllerBase::getOne(req, std::move(callback), std::move(id));
}

void TagsController::updateOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Tags::PrimaryKeyType&& id)
{
    TagsControllerBase::updateOne(req, std::move(callback), std::move(id));
}

void TagsController::deleteOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Tags::PrimaryKeyType&& id)
{
    TagsControllerBase::deleteOne(req, std::move(callback), std::move(id));
}

void TagsController::get(const HttpRequestPtr& req,
                         std::function<void(const HttpResponsePtr&)>&& callback)
{
    TagsControllerBase::get(req, std::move(callback));
}

void TagsController::create(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    TagsControllerBase::create(req, std::move(callback));
}
