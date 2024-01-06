/**
 *
 *  PostMediaController.cc
 *  This file is generated by drogon_ctl
 *
 */

#include "PostMediaController.h"
#include <string>

void PostMediaController::getOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    PostMedia::PrimaryKeyType&& id)
{
    PostMediaControllerBase::getOne(req, std::move(callback), std::move(id));
}

void PostMediaController::updateOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    PostMedia::PrimaryKeyType&& id)
{
    PostMediaControllerBase::updateOne(req, std::move(callback), std::move(id));
}

void PostMediaController::deleteOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    PostMedia::PrimaryKeyType&& id)
{
    PostMediaControllerBase::deleteOne(req, std::move(callback), std::move(id));
}

void PostMediaController::get(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    PostMediaControllerBase::get(req, std::move(callback));
}

void PostMediaController::create(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    PostMediaControllerBase::create(req, std::move(callback));
}