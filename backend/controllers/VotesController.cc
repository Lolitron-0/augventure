#include "VotesController.h"
#include <string>

void VotesController::getOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Tags::PrimaryKeyType&& id)
{
    VotesControllerBase::getOne(req, std::move(callback), std::move(id));
}

void VotesController::updateOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Tags::PrimaryKeyType&& id)
{
    VotesControllerBase::updateOne(req, std::move(callback), std::move(id));
}

void VotesController::deleteOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Tags::PrimaryKeyType&& id)
{
    VotesControllerBase::deleteOne(req, std::move(callback), std::move(id));
}

void VotesController::get(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    VotesControllerBase::get(req, std::move(callback));
}

void VotesController::create(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    VotesControllerBase::create(req, std::move(callback));
}
