#include "UsersController.h"
#include "utils/Macros.h"
#include "utils/Utils.h"
#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>
#include <drogon/HttpTypes.h>
#include <drogon/MultiPart.h>
#include <drogon/UploadFile.h>
#include <drogon/orm/Mapper.h>
#include <string>
#include <trantor/utils/Date.h>
#include <trantor/utils/Logger.h>

void UsersController::getOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Users::PrimaryKeyType&& id)
{
    UsersControllerBase::getOne(req, std::move(callback), std::move(id));
}

void UsersController::updateOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Users::PrimaryKeyType&& id)
{
    UsersControllerBase::updateOne(req, std::move(callback), std::move(id));
}

void UsersController::deleteOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Users::PrimaryKeyType&& id)
{
    UsersControllerBase::deleteOne(req, std::move(callback), std::move(id));
}

void UsersController::get(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    UsersControllerBase::get(req, std::move(callback));
}

void UsersController::create(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    UsersControllerBase::create(req, std::move(callback));
}

void UsersController::uploadPfp(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{

    auto currentUserId{ CURRENT_USER_ID(req) };
    auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };
    auto dbClient{ drogon::app().getDbClient() };
    Mapper<User> mapper{ dbClient };
    mapper.findByPrimaryKey(
        currentUserId,
        [req, callbackPtr, mapper](User currentUser) mutable
        {
            MultiPartParser fileUploadParser{};
            if (fileUploadParser.parse(req) != 0 ||
                fileUploadParser.getFiles().size() != 1)
            {
                SEND_RESPONSE(*callbackPtr, "Must contain one file",
                              drogon::k400BadRequest);
            }

            // max file size is set in client_max_body_size
            auto& file = fileUploadParser.getFiles()[0];

            if (!augventure::utils::isImageExtension(file.getFileExtension()))
            {
                SEND_RESPONSE(*callbackPtr, "Not supported image type",
                              drogon::k400BadRequest);
            }

            auto md5 = file.getMd5();
            LOG_TRACE << "File's MD5 hash: " + md5;
            LOG_TRACE << "File size: " << file.fileLength();
			
            auto timestampedFileName{ file.getFileName() };
            auto dotIt{ timestampedFileName.find(".") };
            auto now{ trantor::Date::now() };
            timestampedFileName.insert(
                dotIt, std::to_string(now.microSecondsSinceEpoch()));
            file.saveAs(timestampedFileName);

            currentUser.setPfpUrl(app().getUploadPath() + "/" +
                                  timestampedFileName);

            mapper.update(
                currentUser,
                [callbackPtr, pfpPath = currentUser.getValueOfPfpUrl()](auto)
                { SEND_RESPONSE(*callbackPtr, "New pfp url: " + pfpPath); },
                DB_EXCEPTION_HANDLER(*callbackPtr));
        },
        DB_EXCEPTION_HANDLER(callback));
}
