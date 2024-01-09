#include "UsersController.h"
#include "utils/Macros.h"
#include "utils/Utils.h"
#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>
#include <drogon/HttpTypes.h>
#include <drogon/MultiPart.h>
#include <drogon/UploadFile.h>
#include <drogon/orm/Mapper.h>
#include <sodium.h>
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

void UsersController::passwordReset(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    using namespace drogon_model::augventure_db;
    using namespace drogon::orm;

    auto dbClient{ drogon::app().getDbClient() };
    Mapper<User> mapper{ dbClient };

    auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };
    auto currentUserId{ CURRENT_USER_ID(req) }; // filter guarantees result

    mapper.findByPrimaryKey(
        currentUserId,
        [=](User currentUser)
        {
            Json::Value jsonPasswords{ *(req->getJsonObject()) };

            std::string oldPassword{ jsonPasswords["old_password"].asString() };

            if (crypto_pwhash_str_verify(
                    currentUser.getValueOfPassword().c_str(),
                    oldPassword.c_str(), oldPassword.length()) == 0)
            {
                std::string newPassword{
                    jsonPasswords["new_password"].asString()
                };
                char hashedNewPassword[crypto_pwhash_STRBYTES];
                if (crypto_pwhash_str(hashedNewPassword, newPassword.c_str(),
                                      newPassword.length(),
                                      crypto_pwhash_OPSLIMIT_MODERATE,
                                      crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0)
                { // testing only
                    std::cerr << "out of memory!\n";
                }
                currentUser.setPassword(hashedNewPassword);

                Mapper<User> updateMapper{ dbClient };
                updateMapper.update(
                    currentUser,
                    [=](size_t) {
                        (*callbackPtr)(HttpResponse::newHttpResponse(
                            k202Accepted, CT_NONE));
                    },
                    DB_EXCEPTION_HANDLER(*callbackPtr));
            }
            else
            {
                auto resp{ HttpResponse::newHttpResponse(k401Unauthorized,
                                                         CT_TEXT_PLAIN) };
                resp->setBody("wrong_old_password");
                (*callbackPtr)(resp);
            }
        },
        DB_EXCEPTION_HANDLER(callback));
}
void UsersController::profile(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{
    using namespace drogon_model::augventure_db;
    using namespace drogon::orm;

    auto dbClient{ drogon::app().getDbClient() };
    Mapper<User> mapper{ dbClient };

    auto callbackPtr{ MAKE_CALLBACK_HEAP_PTR(callback) };
    auto currentUserId{ CURRENT_USER_ID(req) }; // filter guarantees result
    mapper.findByPrimaryKey(
        currentUserId,
        [=](User currentUser)
        {
            auto response{ drogon::HttpResponse::newHttpJsonResponse(
                Json::Value{}) };
            (*response->jsonObject())["user"] = currentUser.toJson();
            LOG_TRACE << "currentUser : ok";
            (*callbackPtr)(response);
        },
        [=](const DrogonDbException& e)
        {
            auto resp{ drogon::HttpResponse::newHttpResponse(k400BadRequest,
                                                             CT_TEXT_PLAIN) };
            resp->setBody("database exception: " +
                          (std::string)e.base().what());
            (*callbackPtr)(resp);
        });
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
