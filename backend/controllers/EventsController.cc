#include "EventsController.h"
#include "Models.h"
#include "Posts.h"
#include "Sprints.h"
#include "controllers/PostsController.h"
#include "controllers/SprintsController.h"
#include "plugins/JWTService.h"
#include "plugins/StateUpdateScheduler.h"
#include "utils/Macros.h"
#include "utils/Utils.h"
#include <algorithm>
#include <drogon/DrClassMap.h>
#include <drogon/HttpClient.h>
#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>
#include <drogon/HttpTypes.h>
#include <drogon/drogon_callbacks.h>
#include <drogon/orm/Criteria.h>
#include <drogon/orm/Exception.h>
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Result.h>
#include <json/value.h>
#include <json/writer.h>
#include <memory>
#include <utility>

void EventsController::getOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Events::PrimaryKeyType&& id)
{
    auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };
    EventsControllerBase::getOne(
        req,
        [callbackPtr](const HttpResponsePtr& resp)
        {
            if (resp->statusCode() != k200OK)
            {
                (*callbackPtr)(resp);
                return;
            }

            auto dbClient{ drogon::app().getDbClient() };
            Mapper<Sprint> sprintMapper{ dbClient };

            getFullEventData(
                *resp->jsonObject(), [callbackPtr](const Json::Value& result)
                { (*callbackPtr)(HttpResponse::newHttpJsonResponse(result)); },
                DB_EXCEPTION_HANDLER(*callbackPtr));
        },
        std::move(id));
}

void EventsController::updateOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Events::PrimaryKeyType&& id)
{
    EventsControllerBase::updateOne(req, std::move(callback), std::move(id));
}

void EventsController::deleteOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Events::PrimaryKeyType&& id)
{
    auto dbClient{ drogon::app().getDbClient() };
    Mapper<Event> mapper{ dbClient };
    auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };
    auto currentUserId{ CURRENT_USER_ID(req) };

    mapper.findByPrimaryKey(
        id,
        [currentUserId, id, callbackPtr, req,
         this](Event eventToDelete) mutable // id gets const qual and cannot be
                                            // binded to rval
        {
            if (eventToDelete.getValueOfAuthorId() == currentUserId)
            {
                drogon::app()
                    .getPlugin<augventure::plugins::StateUpdateScheduler>()
                    ->removeTaskByKey(id);

                EventsControllerBase::deleteOne(req, std::move(*callbackPtr),
                                                std::move(id));
            }
            else
            {
                auto response{ HttpResponse::newHttpResponse(
                    drogon::k403Forbidden, drogon::CT_TEXT_PLAIN) };
                response->setBody("you are not the owner");
                (*callbackPtr)(response);
            }
        },
        DB_EXCEPTION_HANDLER(*callbackPtr));
}

void EventsController::get(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };
    EventsControllerBase::get(
        req,
        [callbackPtr](const HttpResponsePtr& resp)
        {
            if (resp->statusCode() != k200OK || resp->jsonObject()->empty())
            {
                (*callbackPtr)(resp);
                return;
            }
            expandEventList(
                *resp->jsonObject(),
                [callbackPtr](auto result) {
                    (*callbackPtr)(
                        HttpResponse::newHttpJsonResponse(std::move(result)));
                },

                DB_EXCEPTION_HANDLER(*callbackPtr));
        });
}

void EventsController::create(
    const HttpRequestPtr& eventCreationRequest,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    auto eventRequestJsonPtr{ eventCreationRequest->jsonObject() };
    Json::Value eventRequestJson;
    auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };
    if (eventRequestJsonPtr)
    {
        (*eventRequestJsonPtr)["event"][Events::Cols::_author_id] =
            CURRENT_USER_ID(eventCreationRequest);
        eventRequestJson = Json::Value{ *eventRequestJsonPtr };
        (*eventRequestJsonPtr) =
            (*eventRequestJsonPtr)["event"]; // leaving only event creation json
    }
    EventsControllerBase::create(
        eventCreationRequest,
        [callbackPtr, eventCreationRequest, eventRequestJson,
         this](const HttpResponsePtr& eventCreationResponse)
        {
            if (eventCreationResponse->statusCode() ==
                drogon::k200OK) // if event creation successful
                                // -> try create sprint
            {
                using namespace augventure::plugins;
                auto eventJson{ *eventCreationResponse->jsonObject() };
                drogon::app().getPlugin<StateUpdateScheduler>()->schedule(
                    StateUpdateScheduler::TaskType::EventStart,
                    dateFromJsonString(eventJson["start"].asString()),
                    eventJson["id"].as<PrimaryKeyType>());

                Json::Value initialSprintJson{};
                initialSprintJson[Sprints::Cols::_event_id] =
                    eventJson["id"].as<PrimaryKeyType>();
                initialSprintJson[Sprints::Cols::_state] = "ended";
                auto sprintCreationRequest{
                    drogon::HttpRequest::newHttpJsonRequest(initialSprintJson)
                };
                sprintCreationRequest->setMethod(drogon::Post);
                DrClassMap::getSingleInstance<SprintsController>()->create(
                    sprintCreationRequest,
                    [callbackPtr, eventCreationResponse, eventCreationRequest,
                     eventRequestJson,
                     this](const HttpResponsePtr& sprintCreationResponse)
                    {
                        if (sprintCreationResponse->statusCode() ==
                            k200OK) // if sprint created -> try create initial
                        // post
                        {
                            auto initialPostJson{
                                eventRequestJson["initialPost"]
                            };
                            initialPostJson[Posts::Cols::_sprint_id] =
                                (*sprintCreationResponse
                                      ->getJsonObject())[Sprints::Cols::_id]
                                    .as<PrimaryKeyType>();
                            auto initialPostCreationRequest{
                                drogon::HttpRequest::newHttpJsonRequest(
                                    initialPostJson)
                            };
                            initialPostCreationRequest->setMethod(drogon::Post);
                            DrClassMap::getSingleInstance<PostsController>()->create(
                                initialPostCreationRequest,
                                [callbackPtr, eventCreationResponse,
                                 eventRequestJson,
                                 this](const HttpResponsePtr&
                                           initialPostCreationResponse)
                                {
                                    if (initialPostCreationResponse
                                            ->statusCode() == k200OK)
                                    {

                                        Json::Value firstSprintJson{};
                                        firstSprintJson
                                            [Sprints::Cols::_event_id] =
                                                (*eventCreationResponse
                                                      ->jsonObject())["id"]
                                                    .as<PrimaryKeyType>();
                                        firstSprintJson[Sprints::Cols::_state] =
                                            "voting";
                                        auto firstSprintCreationRequest{
                                            drogon::HttpRequest::
                                                newHttpJsonRequest(
                                                    firstSprintJson)
                                        };
                                        firstSprintCreationRequest->setMethod(
                                            drogon::Post);
                                        DrClassMap::getSingleInstance<
                                            SprintsController>()
                                            ->create(
                                                firstSprintCreationRequest,
                                                [callbackPtr,
                                                 eventCreationResponse, this,
                                                 eventRequestJson](
                                                    auto&&
                                                        firstSprintCreationResponse)
                                                {
                                                    if (firstSprintCreationResponse
                                                            ->statusCode() ==
                                                        k200OK)
                                                    {
                                                        (*callbackPtr)(
                                                            eventCreationResponse);
                                                    }
                                                    else // first sprint
                                                         // creation failed
                                                    {
                                                        deleteOne(
                                                            HttpRequest::
                                                                newHttpRequest(),
                                                            AdviceCallback{},
                                                            eventRequestJson
                                                                [Events::Cols::
                                                                     _id]
                                                                    .as<PrimaryKeyType>());
                                                        (*callbackPtr)(
                                                            firstSprintCreationResponse);
                                                    }
                                                });
                                    }
                                    else // initial post creation failed
                                    {
                                        deleteOne(
                                            HttpRequest::newHttpRequest(),
                                            AdviceCallback{},
                                            eventRequestJson[Events::Cols::_id]
                                                .as<PrimaryKeyType>());
                                        (*callbackPtr)(
                                            initialPostCreationResponse);
                                    }
                                });
                        }
                        else // sprint creation failed
                        {
                            deleteOne(HttpRequest::newHttpRequest(),
                                      AdviceCallback{},
                                      eventRequestJson[Events::Cols::_id]
                                          .as<PrimaryKeyType>());
                            (*callbackPtr)(sprintCreationResponse);
                        }
                    });
            }
            else // event creation failed
            {
                deleteOne(
                    HttpRequest::newHttpRequest(), AdviceCallback{},
                    eventRequestJson[Events::Cols::_id].as<PrimaryKeyType>());
                (*callbackPtr)(eventCreationResponse);
            }
        });
}
