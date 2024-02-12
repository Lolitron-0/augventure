#include "SuggestionsController.h"
#include "Models.h"
#include "PostMedia.h"
#include "Posts.h"
#include "Suggestions.h"
#include "Votes.h"
#include "controllers/PostsController.h"
#include "controllers/SuggestionsControllerBase.h"
#include "controllers/VotesController.h"
#include "plugins/JWTService.h"
#include "utils/Macros.h"
#include "utils/Utils.h"
#include <drogon/DrClassMap.h>
#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>
#include <drogon/HttpTypes.h>

#include <drogon/drogon_callbacks.h>
#include <drogon/orm/Criteria.h>
#include <drogon/orm/Exception.h>
#include <json/value.h>
#include <string>

void SuggestionsController::getOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Suggestions::PrimaryKeyType&& id)
{
    SuggestionsControllerBase::getOne(req, std::move(callback), std::move(id));
}

void SuggestionsController::updateOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Suggestions::PrimaryKeyType&& id)
{
    SuggestionsControllerBase::updateOne(req, std::move(callback),
                                         std::move(id));
}

void SuggestionsController::vote(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Suggestions::PrimaryKeyType&& id)
{
    auto reqJson{ req->jsonObject() };
    auto errResp{ HttpResponse::newHttpResponse(drogon::k400BadRequest,
                                                drogon::CT_TEXT_PLAIN) };
    if (!reqJson)
    {
        errResp->setBody("No JSON found in request!");
        callback(errResp);
        return;
    }

    auto voteValue{ reqJson->get("vote_value", -10).asInt() };
    if (voteValue != -1 && voteValue != 1 && voteValue != 0)
    {
        errResp->setBody("Invalid request JSON!");
        callback(errResp);
        return;
    }

    auto currentUserId{ CURRENT_USER_ID(req) };
    auto dbClient{ drogon::app().getDbClient() };
    auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };
    Mapper<Votes> votesMapper{ dbClient };
    votesMapper.findOne(
        Criteria{ Votes::Cols::_suggestion_id, CompareOperator::EQ, id } &&
            Criteria{ Votes::Cols::_user_id, CompareOperator::EQ,
                      currentUserId },
        [callbackPtr, votesMapper, currentUserId,
         voteValue](Vote currentVote) mutable // uuh errrmmm ummm uuuuh
        {
            if (currentVote.getValueOfVoteValue() == voteValue)
            {
                auto resp{ HttpResponse::newHttpResponse(
                    drogon::k400BadRequest, drogon::CT_TEXT_PLAIN) };
                resp->setBody("Illegal vote");
                (*callbackPtr)(resp);
                return;
            }

            currentVote.setVoteValue(voteValue);
            votesMapper
                .update( // probably easier to call directly as object is valid
                         // and creating request is too much fucking work
                    currentVote,
                    [callbackPtr, voteValue](auto)
                    {
                        auto resp{ HttpResponse::newHttpResponse(
                            drogon::k200OK, drogon::CT_TEXT_PLAIN) };
                        resp->setBody(
                            "successful " +
                            std::string{ voteValue == 0 ? "un" : "" } + "vote");
                        (*callbackPtr)(resp);
                    },
                    DB_EXCEPTION_HANDLER(*callbackPtr));
        },
        [callbackPtr, votesMapper, dbClient, id, currentUserId,
         voteValue](auto&& e) mutable
        {
            const auto* ur{ dynamic_cast<const UnexpectedRows*>(&e.base()) };
            if (ur) // no votes yet
            {
                Json::Value newVoteJson{};
                newVoteJson[Votes::Cols::_suggestion_id] = id;
                newVoteJson[Votes::Cols::_user_id] = currentUserId;
                newVoteJson[Votes::Cols::_vote_value] = voteValue;
                auto voteCreationRequest{ HttpRequest::newHttpJsonRequest(
                    newVoteJson) };
                DrClassMap::getSingleInstance<VotesController>()->create(
                    voteCreationRequest, std::move(*callbackPtr));
                return;
            }
            std::invoke(DB_EXCEPTION_HANDLER(*callbackPtr), e);
        });
}

void SuggestionsController::deleteOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Suggestions::PrimaryKeyType&& id)
{
    auto dbClient{ drogon::app().getDbClient() };
    Mapper<Suggestions> mapper{ dbClient };
    auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };
    auto currentUserId{ CURRENT_USER_ID(req) };

    mapper.findByPrimaryKey(
        id,
        [currentUserId, id, callbackPtr, req,
         this](auto suggestionToDelete) mutable
        {
            if (suggestionToDelete.getValueOfAuthorId() == currentUserId)
            {

                SuggestionsControllerBase::deleteOne(
                    req, std::move(*callbackPtr), std::move(id));
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

    SuggestionsControllerBase::deleteOne(req, std::move(callback),
                                         std::move(id));
}

void SuggestionsController::get(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };
    auto sortingParams{ req->parameters().find("sort") };
    int8_t sortByVotes{ 0 };
    if (sortingParams != req->parameters().end())
    {
        std::string sortParamsResString{};
        auto sortFields =
            drogon::utils::splitString(sortingParams->second, ",");
        for (auto sortField : sortFields)
        {
            if (sortField == "+votes" || sortField == "votes")
                sortByVotes = 1;
            else if (sortField == "-votes")
                sortByVotes = -1;
            else
                sortParamsResString += sortField + ",";
        }
        if (!sortParamsResString.empty()) // last comma
            sortParamsResString.erase(sortParamsResString.size() - 1);
        req->setParameter("sort", sortParamsResString);
    }

    SuggestionsControllerBase::get(
        req,
        [callbackPtr, sortByVotes](auto resp)
        {
            if (resp->statusCode() != k200OK || resp->jsonObject()->empty())
            {
                (*callbackPtr)(resp);
                return;
            }

            expandSuggestionList(
                *resp->jsonObject(), sortByVotes, [callbackPtr](auto json)
                { (*callbackPtr)(HttpResponse::newHttpJsonResponse(json)); },
                DB_EXCEPTION_HANDLER(*callbackPtr));
        });
}

void SuggestionsController::create(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    auto reqJson{ req->jsonObject() };
    Json::Value initialRequestJson{};
    if (reqJson)
    {
        (*reqJson)["suggestion"][Suggestions::Cols::_author_id] =
            CURRENT_USER_ID(req);
        initialRequestJson = std::move(*reqJson);
        *reqJson = initialRequestJson["suggestion"];
    }

    auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };
    SuggestionsControllerBase::create(
        req,
        [callbackPtr, initialRequestJson, this](auto suggestionCreationResponse)
        {
            if (suggestionCreationResponse->statusCode() != k200OK)
            {
                (*callbackPtr)(std::move(suggestionCreationResponse));
                return;
            }

            auto postJson{ initialRequestJson["content"] };
            postJson[Posts::Cols::_suggestion_id] =
                (*suggestionCreationResponse
                      ->jsonObject())[Suggestions::Cols::_id];
            auto postCreationRequest{ drogon::HttpRequest::newHttpJsonRequest(
                postJson) };
            postCreationRequest->setMethod(drogon::Post);
            DrClassMap::getSingleInstance<PostsController>()->create(
                postCreationRequest,
                [callbackPtr, initialRequestJson, suggestionCreationResponse,
                 this](const auto& postCreationResponse)
                {
                    if (postCreationResponse->statusCode() == k200OK)
                    {

                        (*callbackPtr)(suggestionCreationResponse);
                    }
                    else
                    {
                        deleteOne(HttpRequest::newHttpRequest(),
                                  AdviceCallback{},
                                  initialRequestJson["suggestion"]
                                                    [Suggestions::Cols::_id]
                                                        .as<PrimaryKeyType>());
                        (*callbackPtr)(postCreationResponse);
                    }
                });
        });
}

void SuggestionsController::addMedia(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback, PrimaryKeyType&& id)
{
    auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };

    auto dbClient{ drogon::app().getDbClient() };
    Mapper<Posts> mapper{ dbClient };
    mapper.findOne(
        Criteria{ Posts::Cols::_suggestion_id, CompareOperator::EQ, id },
        [req, callbackPtr](const auto& post)
        {
            MultiPartParser fileUploadParser{};
            auto maxPostMedia{
                app().getCustomConfig()["max_post_media"].asUInt()
            };
            if (fileUploadParser.parse(req) != 0 ||
                fileUploadParser.getFiles().size() > maxPostMedia)
            {
                SEND_RESPONSE(*callbackPtr,
                              "Must contain no more than " +
                                  std::to_string(maxPostMedia) + " files",
                              drogon::k400BadRequest);
            }

            std::vector<Json::Value> postMediaVec{};
            for (auto& file : fileUploadParser.getFiles())
            {
                auto timestampedFileName{
                    augventure::utils::getUniqueFileName(
                        file.getFileName())
                };
                file.saveAs(timestampedFileName);
                Json::Value postMediaJson{};
                postMediaJson[PostMedia::Cols::_post_id] = post.getValueOfId();
                postMediaJson[PostMedia::Cols::_type] =
                    augventure::utils::getMediaTypeString(
                        file.getFileExtension());
                postMediaJson[PostMedia::Cols::_url] =
                    app().getUploadPath().substr(1) + "/" + timestampedFileName;

                postMediaVec.push_back(postMediaJson);
            }
            auto filesUploaded{ fileUploadParser.getFiles().size() };
            createSeveralPostMedia(
                postMediaVec, filesUploaded,
                [callbackPtr, filesUploaded]()
                {
                    SEND_RESPONSE(*callbackPtr,
                                  "Uploaded " + std::to_string(filesUploaded) +
                                      " files");
                },
                DB_EXCEPTION_HANDLER(*callbackPtr));
        },
        DB_EXCEPTION_HANDLER(callback));
}
