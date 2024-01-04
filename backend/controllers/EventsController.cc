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
                HANDLE_DB_EXCEPTION(*callbackPtr));
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
        [callbackPtr](auto e) { handleDatabaseException(e, *callbackPtr); });
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

                HANDLE_DB_EXCEPTION(*callbackPtr));
        });
}

void EventsController::create(
    const HttpRequestPtr& createEventRequest,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    auto eventRequestJsonPtr{ createEventRequest->jsonObject() };
    Json::Value eventRequestJson;
    auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };
    if (eventRequestJsonPtr)
    {
        (*eventRequestJsonPtr)["event"][Events::Cols::_author_id] =
            CURRENT_USER_ID(createEventRequest);
        eventRequestJson = Json::Value{ *eventRequestJsonPtr };
        (*eventRequestJsonPtr) =
            (*eventRequestJsonPtr)["event"]; // leaving only event creation json
    }
    EventsControllerBase::create(
        createEventRequest,
        [callbackPtr, createEventRequest, eventRequestJson,
         this](const HttpResponsePtr& createEventResponse)
        {
            if (createEventResponse->statusCode() ==
                drogon::k200OK) // if event creation successful
                                // -> try create sprint
            {
                using namespace augventure::plugins;
                auto eventJson{ *createEventResponse->jsonObject() };
                drogon::app().getPlugin<StateUpdateScheduler>()->schedule(
                    StateUpdateScheduler::TaskType::EventStart,
                    dateFromJsonString(eventJson["start"].asString()),
                    eventJson["id"].as<PrimaryKeyType>());

                Json::Value initialSprintJson{};
                initialSprintJson[Sprints::Cols::_event_id] =
                    eventJson["id"].as<PrimaryKeyType>();
                initialSprintJson[Sprints::Cols::_state] = "voting";
                auto createSprintRequest{
                    drogon::HttpRequest::newHttpJsonRequest(initialSprintJson)
                };
                createSprintRequest->setMethod(drogon::Post);
                // createSprintRequest->setBody(Json::writeString(
                //     Json::StreamWriterBuilder{}, initialSprint.toJson()));
                DrClassMap::getSingleInstance<SprintsController>()->create(
                    createSprintRequest,
                    [callbackPtr, createEventResponse, createEventRequest,
                     eventRequestJson,
                     this](const HttpResponsePtr& createSprintResponse)
                    {
                        if (createSprintResponse->statusCode() ==
                            k200OK) // if sprint created -> try create initial
                        // post
                        {
                            auto initialPostJson{
                                eventRequestJson["initialPost"]
                            };
                            initialPostJson[Posts::Cols::_sprint_id] =
                                (*createSprintResponse
                                      ->getJsonObject())[Sprints::Cols::_id]
                                    .as<PrimaryKeyType>();
                            auto createInitialPostRequest{
                                drogon::HttpRequest::newHttpJsonRequest(
                                    initialPostJson)
                            };
                            createInitialPostRequest->setMethod(drogon::Post);
                            DrClassMap::getSingleInstance<PostsController>()
                                ->create(
                                    createInitialPostRequest,
                                    [callbackPtr, createEventResponse](
                                        const HttpResponsePtr&
                                            createInitialPostResponse)
                                    {
                                        if (createInitialPostResponse
                                                ->statusCode() == k200OK)
                                        {
                                            (*callbackPtr)(createEventResponse);
                                        }
                                        else // initial post creation failed
                                        {
                                            (*callbackPtr)(
                                                createInitialPostResponse);
                                        }
                                    });
                        }
                        else // sprint creation failed
                        {
                            deleteOne(HttpRequest::newHttpRequest(),
                                      AdviceCallback{},
                                      eventRequestJson[Events::Cols::_id]
                                          .as<PrimaryKeyType>());
                            (*callbackPtr)(createSprintResponse);
                        }
                    });
            }
            else // event creation failed
            {
                deleteOne(
                    HttpRequest::newHttpRequest(), AdviceCallback{},
                    eventRequestJson[Events::Cols::_id].as<PrimaryKeyType>());
                (*callbackPtr)(createEventResponse);
            }
        });
}
