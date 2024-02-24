#include "EventsController.h"
#include "Models.h"
#include "Posts.h"
#include "Sprints.h"
#include "SuggestionsControllerBase.h"
#include "controllers/PostsController.h"
#include "controllers/SprintsController.h"
#include "plugins/JWTService.h"
#include "plugins/StateUpdateScheduler.h"
#include "utils/Macros.h"
#include "utils/Utils.h"

#include <Suggestions.h>
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

void EventsController::finishVoting(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Events::PrimaryKeyType&& id)
{
    auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };
    auto currentUserId{ CURRENT_USER_ID(req) };

    auto dbClient{ app().getDbClient() };
    Mapper<Event> eventMapper{ dbClient };

    auto jsonPtr{ req->jsonObject() };
    if (!jsonPtr || !jsonPtr->isMember(Sprint::Cols::_suggestion_winner_id))
    {
        SEND_RESPONSE(callback, "Request body is ill-formed", k400BadRequest);
    }

    eventMapper.findByPrimaryKey(
        id,
        [jsonPtr, dbClient, callbackPtr, currentUserId](Event event)
        {
            if (event.getValueOfAuthorId() == currentUserId)
            {
                Mapper<Sprint> sprintMapper{ dbClient };
                sprintMapper.findOne(
                    Criteria{ Sprints::Cols::_event_id, CompareOperator::EQ,
                              event.getValueOfId() } &&
                        Criteria{ Sprints::Cols::_state, CompareOperator::EQ,
                                  "voting" },
                    [jsonPtr, dbClient, sprintMapper,
                     callbackPtr](Sprint activeSprint) mutable
                    {
                        auto suggestionWinnerId{
                            (*jsonPtr)[Sprints::Cols::_suggestion_winner_id]
                                .as<PrimaryKeyType>()
                        };
                        Mapper<Suggestions> suggestionsMapper{ dbClient };
                        suggestionsMapper.findByPrimaryKey(
                            suggestionWinnerId,
                            [activeSprint, sprintMapper, suggestionWinnerId,
                             callbackPtr](auto winnerSuggestion) mutable
                            {
                                if (winnerSuggestion.getValueOfSprintId() !=
                                    activeSprint.getValueOfId())
                                {
                                    SEND_RESPONSE(
                                        *callbackPtr,
                                        "Suggestion from another sprint",
                                        k400BadRequest);
									return;
                                }
                                activeSprint.setState("implementing");
                                activeSprint.setSuggestionWinnerId(
                                    suggestionWinnerId);
                                sprintMapper.update(
                                    activeSprint,
                                    [activeSprint, sprintMapper,
                                     callbackPtr](auto) {
                                        (*callbackPtr)(
                                            HttpResponse::newHttpResponse());
                                    },
                                    DB_EXCEPTION_HANDLER(*callbackPtr));
                            },
                            DB_EXCEPTION_HANDLER(*callbackPtr));
                    },
                    DB_EXCEPTION_HANDLER(*callbackPtr));
            }
            else
            {
                auto resp{ HttpResponse::newHttpResponse(
                    k400BadRequest, ContentType::CT_TEXT_PLAIN) };
                resp->setBody("You are not the owner");
                (*callbackPtr)(resp);
            }
        },
        DB_EXCEPTION_HANDLER(*callbackPtr));
}

void EventsController::finishImplementing(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Events::PrimaryKeyType&& id)
{
    auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };

    auto reqJson{ req->jsonObject() };
    auto currentUserId{ CURRENT_USER_ID(req) };

    if (!reqJson->isMember("content"))
    {
        SEND_RESPONSE(callback, "No content is found in the request",
                      k400BadRequest);
        return;
    }

    if (!reqJson->isMember("is_last_sprint"))
    {
        SEND_RESPONSE(*callbackPtr,
                      "No info about last sprint is found in the request",
                      k400BadRequest);
        return;
    }

    auto dbClient{ app().getDbClient() };
    Mapper<Event> eventMapper{ dbClient };
    eventMapper.findOne(
        Criteria{ Events::Cols::_id, CompareOperator::EQ, id } &&
            Criteria{ Events::Cols::_author_id, CompareOperator::EQ,
                      currentUserId },
        [reqJson, dbClient, callbackPtr](Event event)
        {
            Mapper<Sprint> sprintMapper{ dbClient };

            sprintMapper.findOne(
                Criteria{ Sprints::Cols::_event_id, CompareOperator::EQ,
                          event.getValueOfId() } &&
                    Criteria{ Sprints::Cols::_state, CompareOperator::EQ,
                              "implementing" },
                [reqJson, sprintMapper, callbackPtr,
                 event](Sprint sprint) mutable
                {
                    auto postJson{ (*reqJson)["content"] };
                    postJson[Posts::Cols::_sprint_id] = sprint.getValueOfId();
                    auto postCreationRequest{
                        drogon::HttpRequest::newHttpJsonRequest(postJson)
                    };

                    DrClassMap::getSingleInstance<PostsController>()->create(
                        postCreationRequest,
                        [sprint, sprintMapper, reqJson, event,
                         callbackPtr](const auto& postCreationResponse) mutable
                        {
                            if (postCreationResponse->statusCode() == k200OK)
                            {
                                sprint.setState("ended");
                                sprintMapper.update(
                                    sprint,
                                    [callbackPtr, reqJson, event,
                                     postCreationResponse,
                                     sprintMapper](auto) mutable
                                    {
                                        if ((*reqJson)["is_last_sprint"]
                                                .asBool())
                                        {
                                            event.setState("ended");
                                            auto dbClient{
                                                app().getDbClient()
                                            };
                                            Mapper<Event> eventMapper{
                                                dbClient
                                            };
                                            eventMapper.update(
                                                event,
                                                [postCreationResponse,
                                                 callbackPtr](auto) {
                                                    (*callbackPtr)(
                                                        postCreationResponse);
                                                },
                                                DB_EXCEPTION_HANDLER(
                                                    *callbackPtr));
                                        }
                                        else
                                        {
                                            Json::Value nextSprintJson;
                                            nextSprintJson["event_id"] =
                                                event.getValueOfId();
                                            nextSprintJson["state"] = "voting";
                                            Sprints nextSprint{
                                                nextSprintJson
                                            };
                                            sprintMapper.insert(
                                                nextSprint,
                                                [postCreationResponse,
                                                 callbackPtr](auto) {
                                                    (*callbackPtr)(
                                                        postCreationResponse);
                                                },
                                                DB_EXCEPTION_HANDLER(
                                                    *callbackPtr));
                                        }
                                    },
                                    DB_EXCEPTION_HANDLER(*callbackPtr));
                            }
                            else
                            {
                                // nothing bad happened
                                (*callbackPtr)(postCreationResponse);
                            }
                        });
                },
                DB_EXCEPTION_HANDLER(*callbackPtr));
        },
        DB_EXCEPTION_HANDLER(*callbackPtr));
}

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
        [currentUserId, id, callbackPtr, req, this](Event eventToDelete) mutable
        // id gets const qual and cannot be
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
                response->setBody("You are not the owner");
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
        [callbackPtr, eventCreationRequest, eventRequestJson](
            const HttpResponsePtr &eventCreationResponse)
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
                    [callbackPtr, eventCreationResponse, eventCreationRequest, eventRequestJson](
                        const HttpResponsePtr &sprintCreationResponse)
                    {
                        if (sprintCreationResponse->statusCode() ==
                            k200OK) // if sprint created -> try create initial
                        // post
                        {
                            auto initialPostJson{
                                eventRequestJson["initial_post"]
                            };
                            initialPostJson[Posts::Cols::_sprint_id] =
                                (*sprintCreationResponse
                                      ->getJsonObject())[Sprints::Cols::_id]
                                    .as<PrimaryKeyType>();
                            auto initialPostCreationRequest{
                                drogon::HttpRequest::newHttpJsonRequest(
                                    initialPostJson)
                            };
                            DrClassMap::getSingleInstance<PostsController>()->create(
                                initialPostCreationRequest,
                                [callbackPtr, eventCreationResponse, eventRequestJson](
                                    const HttpResponsePtr &initialPostCreationResponse)
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
                                        DrClassMap::getSingleInstance<SprintsController>()->create(
                                            firstSprintCreationRequest,
                                            [callbackPtr, eventCreationResponse, eventRequestJson](
                                                auto &&firstSprintCreationResponse)
                                            {
                                                if (firstSprintCreationResponse->statusCode()
                                                    == k200OK)
                                                {
                                                    (*callbackPtr)(eventCreationResponse);
                                                }
                                                else // first sprint
                                                // creation failed
                                                {
                                                    auto dbClient{drogon::app().getDbClient()};
                                                    Mapper<Event> deleteMapper{dbClient};
                                                    deleteMapper.deleteByPrimaryKey(
                                                        eventRequestJson[Events::Cols::_id]
                                                            .as<PrimaryKeyType>(),
                                                        [callbackPtr,
                                                         firstSprintCreationResponse](auto) {
                                                            (*callbackPtr)(
                                                                firstSprintCreationResponse);
                                                        },
                                                        DB_EXCEPTION_HANDLER(*callbackPtr));
                                                }
                                            });
                                    }
                                    else // initial post creation failed
                                    {
                                        auto dbClient{drogon::app().getDbClient()};
                                        Mapper<Event> deleteMapper{dbClient};
                                        deleteMapper.deleteByPrimaryKey(
                                            eventRequestJson[Events::Cols::_id].as<PrimaryKeyType>(),
                                            [callbackPtr, initialPostCreationResponse](auto)
                                            { (*callbackPtr)(initialPostCreationResponse); },
                                            DB_EXCEPTION_HANDLER(*callbackPtr));
                                    }
                                });
                        }
                        else // sprint creation failed
                        {
                            auto dbClient{drogon::app().getDbClient()};
                            Mapper<Event> deleteMapper{dbClient};
                            deleteMapper.deleteByPrimaryKey(
                                eventRequestJson[Events::Cols::_id].as<PrimaryKeyType>(),
                                [callbackPtr, sprintCreationResponse](auto)
                                { (*callbackPtr)(sprintCreationResponse); },
                                DB_EXCEPTION_HANDLER(*callbackPtr));
                        }
                    });
            }
            else // event creation failed
            {
                (*callbackPtr)(eventCreationResponse);
            }
        });
}
