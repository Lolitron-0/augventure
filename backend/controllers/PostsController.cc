#include "PostsController.h"
#include "utils/Macros.h"
#include <string>

void PostsController::getOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Posts::PrimaryKeyType&& id)
{
    PostsControllerBase::getOne(req, std::move(callback), std::move(id));
}

void PostsController::updateOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Posts::PrimaryKeyType&& id)
{
    PostsControllerBase::updateOne(req, std::move(callback), std::move(id));
}

void PostsController::deleteOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Posts::PrimaryKeyType&& id)
{
    PostsControllerBase::deleteOne(req, std::move(callback), std::move(id));
}

void PostsController::get(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    PostsControllerBase::get(req, std::move(callback));
}

void PostsController::create(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    PostsControllerBase::create(req, std::move(callback));
}

void PostsController::addMedia(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Posts::PrimaryKeyType&& id)
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
                    augventure::utils::getTimestampedFileName(
                        file.getFileName())
                };
                file.saveAs(timestampedFileName);
                Json::Value postMediaJson{};
                postMediaJson[PostMedia::Cols::_post_id] = post.getValueOfId();
                postMediaJson[PostMedia::Cols::_type] =
                    augventure::utils::getMediaTypeString(
                        file.getFileExtension());
                postMediaJson[PostMedia::Cols::_url] =
                    app().getUploadPath() + "/" + timestampedFileName;

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
