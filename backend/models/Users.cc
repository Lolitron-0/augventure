/**
 *
 *  Users.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "Users.h"
#include "Events.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::augventure_db;

const std::string Users::Cols::_id = "id";
const std::string Users::Cols::_email = "email";
const std::string Users::Cols::_password = "password";
const std::string Users::Cols::_username = "username";
const std::string Users::Cols::_pfp_url = "pfp_url";
const std::string Users::Cols::_bio = "bio";
const std::string Users::Cols::_auth_code = "auth_code";
const std::string Users::primaryKeyName = "id";
const bool Users::hasPrimaryKey = true;
const std::string Users::tableName = "users";

const std::vector<typename Users::MetaData> Users::metaData_ = {
    { "id", "uint32_t", "int(10) unsigned", 4, 1, 1, 1 },
    { "email", "std::string", "char(100)", 0, 0, 0, 1 },
    { "password", "std::string", "tinytext", 0, 0, 0, 1 },
    { "username", "std::string", "char(30)", 0, 0, 0, 1 },
    { "pfp_url", "std::string", "tinytext", 0, 0, 0, 0 },
    { "bio", "std::string", "text", 0, 0, 0, 1 },
    { "auth_code", "std::string", "char(6)", 0, 0, 0, 0 }
};
const std::string& Users::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Users::Users(const Row& r, const ssize_t indexOffset) noexcept
{
    if (indexOffset < 0)
    {
        if (!r["id"].isNull())
        {
            id_ = std::make_shared<uint32_t>(r["id"].as<uint32_t>());
        }
        if (!r["email"].isNull())
        {
            email_ =
                std::make_shared<std::string>(r["email"].as<std::string>());
        }
        if (!r["password"].isNull())
        {
            password_ =
                std::make_shared<std::string>(r["password"].as<std::string>());
        }
        if (!r["username"].isNull())
        {
            username_ =
                std::make_shared<std::string>(r["username"].as<std::string>());
        }
        if (!r["pfp_url"].isNull())
        {
            pfpUrl_ =
                std::make_shared<std::string>(r["pfp_url"].as<std::string>());
        }
        if (!r["bio"].isNull())
        {
            bio_ = std::make_shared<std::string>(r["bio"].as<std::string>());
        }
        if (!r["auth_code"].isNull())
        {
            authCode_ =
                std::make_shared<std::string>(r["auth_code"].as<std::string>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if (offset + 7 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
        index = offset + 0;
        if (!r[index].isNull())
        {
            id_ = std::make_shared<uint32_t>(r[index].as<uint32_t>());
        }
        index = offset + 1;
        if (!r[index].isNull())
        {
            email_ = std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if (!r[index].isNull())
        {
            password_ =
                std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if (!r[index].isNull())
        {
            username_ =
                std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if (!r[index].isNull())
        {
            pfpUrl_ = std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if (!r[index].isNull())
        {
            bio_ = std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if (!r[index].isNull())
        {
            authCode_ =
                std::make_shared<std::string>(r[index].as<std::string>());
        }
    }
}

Users::Users(
    const Json::Value& pJson,
    const std::vector<std::string>& pMasqueradingVector) noexcept(false)
{
    if (pMasqueradingVector.size() != 7)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if (!pMasqueradingVector[0].empty() &&
        pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if (!pJson[pMasqueradingVector[0]].isNull())
        {
            id_ = std::make_shared<uint32_t>(
                (uint32_t)pJson[pMasqueradingVector[0]].asUInt64());
        }
    }
    if (!pMasqueradingVector[1].empty() &&
        pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if (!pJson[pMasqueradingVector[1]].isNull())
        {
            email_ = std::make_shared<std::string>(
                pJson[pMasqueradingVector[1]].asString());
        }
    }
    if (!pMasqueradingVector[2].empty() &&
        pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if (!pJson[pMasqueradingVector[2]].isNull())
        {
            password_ = std::make_shared<std::string>(
                pJson[pMasqueradingVector[2]].asString());
        }
    }
    if (!pMasqueradingVector[3].empty() &&
        pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if (!pJson[pMasqueradingVector[3]].isNull())
        {
            username_ = std::make_shared<std::string>(
                pJson[pMasqueradingVector[3]].asString());
        }
    }
    if (!pMasqueradingVector[4].empty() &&
        pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if (!pJson[pMasqueradingVector[4]].isNull())
        {
            pfpUrl_ = std::make_shared<std::string>(
                pJson[pMasqueradingVector[4]].asString());
        }
    }
    if (!pMasqueradingVector[5].empty() &&
        pJson.isMember(pMasqueradingVector[5]))
    {
        dirtyFlag_[5] = true;
        if (!pJson[pMasqueradingVector[5]].isNull())
        {
            bio_ = std::make_shared<std::string>(
                pJson[pMasqueradingVector[5]].asString());
        }
    }
    if (!pMasqueradingVector[6].empty() &&
        pJson.isMember(pMasqueradingVector[6]))
    {
        dirtyFlag_[6] = true;
        if (!pJson[pMasqueradingVector[6]].isNull())
        {
            authCode_ = std::make_shared<std::string>(
                pJson[pMasqueradingVector[6]].asString());
        }
    }
}

Users::Users(const Json::Value& pJson) noexcept(false)
{
    if (pJson.isMember("id"))
    {
        dirtyFlag_[0] = true;
        if (!pJson["id"].isNull())
        {
            id_ = std::make_shared<uint32_t>((uint32_t)pJson["id"].asUInt64());
        }
    }
    if (pJson.isMember("email"))
    {
        dirtyFlag_[1] = true;
        if (!pJson["email"].isNull())
        {
            email_ = std::make_shared<std::string>(pJson["email"].asString());
        }
    }
    if (pJson.isMember("password"))
    {
        dirtyFlag_[2] = true;
        if (!pJson["password"].isNull())
        {
            password_ =
                std::make_shared<std::string>(pJson["password"].asString());
        }
    }
    if (pJson.isMember("username"))
    {
        dirtyFlag_[3] = true;
        if (!pJson["username"].isNull())
        {
            username_ =
                std::make_shared<std::string>(pJson["username"].asString());
        }
    }
    if (pJson.isMember("pfp_url"))
    {
        dirtyFlag_[4] = true;
        if (!pJson["pfp_url"].isNull())
        {
            pfpUrl_ =
                std::make_shared<std::string>(pJson["pfp_url"].asString());
        }
    }
    if (pJson.isMember("bio"))
    {
        dirtyFlag_[5] = true;
        if (!pJson["bio"].isNull())
        {
            bio_ = std::make_shared<std::string>(pJson["bio"].asString());
        }
    }
    if (pJson.isMember("auth_code"))
    {
        dirtyFlag_[6] = true;
        if (!pJson["auth_code"].isNull())
        {
            authCode_ =
                std::make_shared<std::string>(pJson["auth_code"].asString());
        }
    }
}

void Users::updateByMasqueradedJson(
    const Json::Value& pJson,
    const std::vector<std::string>& pMasqueradingVector) noexcept(false)
{
    if (pMasqueradingVector.size() != 7)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if (!pMasqueradingVector[0].empty() &&
        pJson.isMember(pMasqueradingVector[0]))
    {
        if (!pJson[pMasqueradingVector[0]].isNull())
        {
            id_ = std::make_shared<uint32_t>(
                (uint32_t)pJson[pMasqueradingVector[0]].asUInt64());
        }
    }
    if (!pMasqueradingVector[1].empty() &&
        pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if (!pJson[pMasqueradingVector[1]].isNull())
        {
            email_ = std::make_shared<std::string>(
                pJson[pMasqueradingVector[1]].asString());
        }
    }
    if (!pMasqueradingVector[2].empty() &&
        pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if (!pJson[pMasqueradingVector[2]].isNull())
        {
            password_ = std::make_shared<std::string>(
                pJson[pMasqueradingVector[2]].asString());
        }
    }
    if (!pMasqueradingVector[3].empty() &&
        pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if (!pJson[pMasqueradingVector[3]].isNull())
        {
            username_ = std::make_shared<std::string>(
                pJson[pMasqueradingVector[3]].asString());
        }
    }
    if (!pMasqueradingVector[4].empty() &&
        pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if (!pJson[pMasqueradingVector[4]].isNull())
        {
            pfpUrl_ = std::make_shared<std::string>(
                pJson[pMasqueradingVector[4]].asString());
        }
    }
    if (!pMasqueradingVector[5].empty() &&
        pJson.isMember(pMasqueradingVector[5]))
    {
        dirtyFlag_[5] = true;
        if (!pJson[pMasqueradingVector[5]].isNull())
        {
            bio_ = std::make_shared<std::string>(
                pJson[pMasqueradingVector[5]].asString());
        }
    }
    if (!pMasqueradingVector[6].empty() &&
        pJson.isMember(pMasqueradingVector[6]))
    {
        dirtyFlag_[6] = true;
        if (!pJson[pMasqueradingVector[6]].isNull())
        {
            authCode_ = std::make_shared<std::string>(
                pJson[pMasqueradingVector[6]].asString());
        }
    }
}

void Users::updateByJson(const Json::Value& pJson) noexcept(false)
{
    if (pJson.isMember("id"))
    {
        if (!pJson["id"].isNull())
        {
            id_ = std::make_shared<uint32_t>((uint32_t)pJson["id"].asUInt64());
        }
    }
    if (pJson.isMember("email"))
    {
        dirtyFlag_[1] = true;
        if (!pJson["email"].isNull())
        {
            email_ = std::make_shared<std::string>(pJson["email"].asString());
        }
    }
    if (pJson.isMember("password"))
    {
        dirtyFlag_[2] = true;
        if (!pJson["password"].isNull())
        {
            password_ =
                std::make_shared<std::string>(pJson["password"].asString());
        }
    }
    if (pJson.isMember("username"))
    {
        dirtyFlag_[3] = true;
        if (!pJson["username"].isNull())
        {
            username_ =
                std::make_shared<std::string>(pJson["username"].asString());
        }
    }
    if (pJson.isMember("pfp_url"))
    {
        dirtyFlag_[4] = true;
        if (!pJson["pfp_url"].isNull())
        {
            pfpUrl_ =
                std::make_shared<std::string>(pJson["pfp_url"].asString());
        }
    }
    if (pJson.isMember("bio"))
    {
        dirtyFlag_[5] = true;
        if (!pJson["bio"].isNull())
        {
            bio_ = std::make_shared<std::string>(pJson["bio"].asString());
        }
    }
    if (pJson.isMember("auth_code"))
    {
        dirtyFlag_[6] = true;
        if (!pJson["auth_code"].isNull())
        {
            authCode_ =
                std::make_shared<std::string>(pJson["auth_code"].asString());
        }
    }
}

const uint32_t& Users::getValueOfId() const noexcept
{
    const static uint32_t defaultValue = uint32_t();
    if (id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<uint32_t>& Users::getId() const noexcept { return id_; }
void Users::setId(const uint32_t& pId) noexcept
{
    id_ = std::make_shared<uint32_t>(pId);
    dirtyFlag_[0] = true;
}
const typename Users::PrimaryKeyType& Users::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string& Users::getValueOfEmail() const noexcept
{
    const static std::string defaultValue = std::string();
    if (email_)
        return *email_;
    return defaultValue;
}
const std::shared_ptr<std::string>& Users::getEmail() const noexcept
{
    return email_;
}
void Users::setEmail(const std::string& pEmail) noexcept
{
    email_ = std::make_shared<std::string>(pEmail);
    dirtyFlag_[1] = true;
}
void Users::setEmail(std::string&& pEmail) noexcept
{
    email_ = std::make_shared<std::string>(std::move(pEmail));
    dirtyFlag_[1] = true;
}

const std::string& Users::getValueOfPassword() const noexcept
{
    const static std::string defaultValue = std::string();
    if (password_)
        return *password_;
    return defaultValue;
}
const std::shared_ptr<std::string>& Users::getPassword() const noexcept
{
    return password_;
}
void Users::setPassword(const std::string& pPassword) noexcept
{
    password_ = std::make_shared<std::string>(pPassword);
    dirtyFlag_[2] = true;
}
void Users::setPassword(std::string&& pPassword) noexcept
{
    password_ = std::make_shared<std::string>(std::move(pPassword));
    dirtyFlag_[2] = true;
}

const std::string& Users::getValueOfUsername() const noexcept
{
    const static std::string defaultValue = std::string();
    if (username_)
        return *username_;
    return defaultValue;
}
const std::shared_ptr<std::string>& Users::getUsername() const noexcept
{
    return username_;
}
void Users::setUsername(const std::string& pUsername) noexcept
{
    username_ = std::make_shared<std::string>(pUsername);
    dirtyFlag_[3] = true;
}
void Users::setUsername(std::string&& pUsername) noexcept
{
    username_ = std::make_shared<std::string>(std::move(pUsername));
    dirtyFlag_[3] = true;
}

const std::string& Users::getValueOfPfpUrl() const noexcept
{
    const static std::string defaultValue = std::string();
    if (pfpUrl_)
        return *pfpUrl_;
    return defaultValue;
}
const std::shared_ptr<std::string>& Users::getPfpUrl() const noexcept
{
    return pfpUrl_;
}
void Users::setPfpUrl(const std::string& pPfpUrl) noexcept
{
    pfpUrl_ = std::make_shared<std::string>(pPfpUrl);
    dirtyFlag_[4] = true;
}
void Users::setPfpUrl(std::string&& pPfpUrl) noexcept
{
    pfpUrl_ = std::make_shared<std::string>(std::move(pPfpUrl));
    dirtyFlag_[4] = true;
}
void Users::setPfpUrlToNull() noexcept
{
    pfpUrl_.reset();
    dirtyFlag_[4] = true;
}

const std::string& Users::getValueOfBio() const noexcept
{
    const static std::string defaultValue = std::string();
    if (bio_)
        return *bio_;
    return defaultValue;
}
const std::shared_ptr<std::string>& Users::getBio() const noexcept
{
    return bio_;
}
void Users::setBio(const std::string& pBio) noexcept
{
    bio_ = std::make_shared<std::string>(pBio);
    dirtyFlag_[5] = true;
}
void Users::setBio(std::string&& pBio) noexcept
{
    bio_ = std::make_shared<std::string>(std::move(pBio));
    dirtyFlag_[5] = true;
}

const std::string& Users::getValueOfAuthCode() const noexcept
{
    const static std::string defaultValue = std::string();
    if (authCode_)
        return *authCode_;
    return defaultValue;
}
const std::shared_ptr<std::string>& Users::getAuthCode() const noexcept
{
    return authCode_;
}
void Users::setAuthCode(const std::string& pAuthCode) noexcept
{
    authCode_ = std::make_shared<std::string>(pAuthCode);
    dirtyFlag_[6] = true;
}
void Users::setAuthCode(std::string&& pAuthCode) noexcept
{
    authCode_ = std::make_shared<std::string>(std::move(pAuthCode));
    dirtyFlag_[6] = true;
}
void Users::setAuthCodeToNull() noexcept
{
    authCode_.reset();
    dirtyFlag_[6] = true;
}

void Users::updateId(const uint64_t id)
{
    id_ = std::make_shared<uint32_t>(static_cast<uint32_t>(id));
}

const std::vector<std::string>& Users::insertColumns() noexcept
{
    static const std::vector<std::string> inCols = { "email",    "password",
                                                     "username", "pfp_url",
                                                     "bio",      "auth_code" };
    return inCols;
}

void Users::outputArgs(drogon::orm::internal::SqlBinder& binder) const
{
    if (dirtyFlag_[1])
    {
        if (getEmail())
        {
            binder << getValueOfEmail();
        }
        else
        {
            binder << nullptr;
        }
    }
    if (dirtyFlag_[2])
    {
        if (getPassword())
        {
            binder << getValueOfPassword();
        }
        else
        {
            binder << nullptr;
        }
    }
    if (dirtyFlag_[3])
    {
        if (getUsername())
        {
            binder << getValueOfUsername();
        }
        else
        {
            binder << nullptr;
        }
    }
    if (dirtyFlag_[4])
    {
        if (getPfpUrl())
        {
            binder << getValueOfPfpUrl();
        }
        else
        {
            binder << nullptr;
        }
    }
    if (dirtyFlag_[5])
    {
        if (getBio())
        {
            binder << getValueOfBio();
        }
        else
        {
            binder << nullptr;
        }
    }
    if (dirtyFlag_[6])
    {
        if (getAuthCode())
        {
            binder << getValueOfAuthCode();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> Users::updateColumns() const
{
    std::vector<std::string> ret;
    if (dirtyFlag_[1])
    {
        ret.push_back(getColumnName(1));
    }
    if (dirtyFlag_[2])
    {
        ret.push_back(getColumnName(2));
    }
    if (dirtyFlag_[3])
    {
        ret.push_back(getColumnName(3));
    }
    if (dirtyFlag_[4])
    {
        ret.push_back(getColumnName(4));
    }
    if (dirtyFlag_[5])
    {
        ret.push_back(getColumnName(5));
    }
    if (dirtyFlag_[6])
    {
        ret.push_back(getColumnName(6));
    }
    return ret;
}

void Users::updateArgs(drogon::orm::internal::SqlBinder& binder) const
{
    if (dirtyFlag_[1])
    {
        if (getEmail())
        {
            binder << getValueOfEmail();
        }
        else
        {
            binder << nullptr;
        }
    }
    if (dirtyFlag_[2])
    {
        if (getPassword())
        {
            binder << getValueOfPassword();
        }
        else
        {
            binder << nullptr;
        }
    }
    if (dirtyFlag_[3])
    {
        if (getUsername())
        {
            binder << getValueOfUsername();
        }
        else
        {
            binder << nullptr;
        }
    }
    if (dirtyFlag_[4])
    {
        if (getPfpUrl())
        {
            binder << getValueOfPfpUrl();
        }
        else
        {
            binder << nullptr;
        }
    }
    if (dirtyFlag_[5])
    {
        if (getBio())
        {
            binder << getValueOfBio();
        }
        else
        {
            binder << nullptr;
        }
    }
    if (dirtyFlag_[6])
    {
        if (getAuthCode())
        {
            binder << getValueOfAuthCode();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value Users::toJson() const
{
    Json::Value ret;
    if (getId())
    {
        ret["id"] = getValueOfId();
    }
    else
    {
        ret["id"] = Json::Value();
    }
    if (getEmail())
    {
        ret["email"] = getValueOfEmail();
    }
    else
    {
        ret["email"] = Json::Value();
    }
    if (getPassword())
    {
        ret["password"] = getValueOfPassword();
    }
    else
    {
        ret["password"] = Json::Value();
    }
    if (getUsername())
    {
        ret["username"] = getValueOfUsername();
    }
    else
    {
        ret["username"] = Json::Value();
    }
    if (getPfpUrl())
    {
        ret["pfp_url"] = getValueOfPfpUrl();
    }
    else
    {
        ret["pfp_url"] = Json::Value();
    }
    if (getBio())
    {
        ret["bio"] = getValueOfBio();
    }
    else
    {
        ret["bio"] = Json::Value();
    }
    if (getAuthCode())
    {
        ret["auth_code"] = getValueOfAuthCode();
    }
    else
    {
        ret["auth_code"] = Json::Value();
    }
    return ret;
}

Json::Value Users::toMasqueradedJson(
    const std::vector<std::string>& pMasqueradingVector) const
{
    Json::Value ret;
    if (pMasqueradingVector.size() == 7)
    {
        if (!pMasqueradingVector[0].empty())
        {
            if (getId())
            {
                ret[pMasqueradingVector[0]] = getValueOfId();
            }
            else
            {
                ret[pMasqueradingVector[0]] = Json::Value();
            }
        }
        if (!pMasqueradingVector[1].empty())
        {
            if (getEmail())
            {
                ret[pMasqueradingVector[1]] = getValueOfEmail();
            }
            else
            {
                ret[pMasqueradingVector[1]] = Json::Value();
            }
        }
        if (!pMasqueradingVector[2].empty())
        {
            if (getPassword())
            {
                ret[pMasqueradingVector[2]] = getValueOfPassword();
            }
            else
            {
                ret[pMasqueradingVector[2]] = Json::Value();
            }
        }
        if (!pMasqueradingVector[3].empty())
        {
            if (getUsername())
            {
                ret[pMasqueradingVector[3]] = getValueOfUsername();
            }
            else
            {
                ret[pMasqueradingVector[3]] = Json::Value();
            }
        }
        if (!pMasqueradingVector[4].empty())
        {
            if (getPfpUrl())
            {
                ret[pMasqueradingVector[4]] = getValueOfPfpUrl();
            }
            else
            {
                ret[pMasqueradingVector[4]] = Json::Value();
            }
        }
        if (!pMasqueradingVector[5].empty())
        {
            if (getBio())
            {
                ret[pMasqueradingVector[5]] = getValueOfBio();
            }
            else
            {
                ret[pMasqueradingVector[5]] = Json::Value();
            }
        }
        if (!pMasqueradingVector[6].empty())
        {
            if (getAuthCode())
            {
                ret[pMasqueradingVector[6]] = getValueOfAuthCode();
            }
            else
            {
                ret[pMasqueradingVector[6]] = Json::Value();
            }
        }
        return ret;
    }
    LOG_ERROR << "Masquerade failed";
    if (getId())
    {
        ret["id"] = getValueOfId();
    }
    else
    {
        ret["id"] = Json::Value();
    }
    if (getEmail())
    {
        ret["email"] = getValueOfEmail();
    }
    else
    {
        ret["email"] = Json::Value();
    }
    if (getPassword())
    {
        ret["password"] = getValueOfPassword();
    }
    else
    {
        ret["password"] = Json::Value();
    }
    if (getUsername())
    {
        ret["username"] = getValueOfUsername();
    }
    else
    {
        ret["username"] = Json::Value();
    }
    if (getPfpUrl())
    {
        ret["pfp_url"] = getValueOfPfpUrl();
    }
    else
    {
        ret["pfp_url"] = Json::Value();
    }
    if (getBio())
    {
        ret["bio"] = getValueOfBio();
    }
    else
    {
        ret["bio"] = Json::Value();
    }
    if (getAuthCode())
    {
        ret["auth_code"] = getValueOfAuthCode();
    }
    else
    {
        ret["auth_code"] = Json::Value();
    }
    return ret;
}

bool Users::validateJsonForCreation(const Json::Value& pJson, std::string& err)
{
    if (pJson.isMember("id"))
    {
        if (!validJsonOfField(0, "id", pJson["id"], err, true))
            return false;
    }
    if (pJson.isMember("email"))
    {
        if (!validJsonOfField(1, "email", pJson["email"], err, true))
            return false;
    }
    else
    {
        err = "The email column cannot be null";
        return false;
    }
    if (pJson.isMember("password"))
    {
        if (!validJsonOfField(2, "password", pJson["password"], err, true))
            return false;
    }
    else
    {
        err = "The password column cannot be null";
        return false;
    }
    if (pJson.isMember("username"))
    {
        if (!validJsonOfField(3, "username", pJson["username"], err, true))
            return false;
    }
    else
    {
        err = "The username column cannot be null";
        return false;
    }
    if (pJson.isMember("pfp_url"))
    {
        if (!validJsonOfField(4, "pfp_url", pJson["pfp_url"], err, true))
            return false;
    }
    if (pJson.isMember("bio"))
    {
        if (!validJsonOfField(5, "bio", pJson["bio"], err, true))
            return false;
    }
    if (pJson.isMember("auth_code"))
    {
        if (!validJsonOfField(6, "auth_code", pJson["auth_code"], err, true))
            return false;
    }
    return true;
}
bool Users::validateMasqueradedJsonForCreation(
    const Json::Value& pJson,
    const std::vector<std::string>& pMasqueradingVector, std::string& err)
{
    if (pMasqueradingVector.size() != 7)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try
    {
        if (!pMasqueradingVector[0].empty())
        {
            if (pJson.isMember(pMasqueradingVector[0]))
            {
                if (!validJsonOfField(0, pMasqueradingVector[0],
                                      pJson[pMasqueradingVector[0]], err, true))
                    return false;
            }
        }
        if (!pMasqueradingVector[1].empty())
        {
            if (pJson.isMember(pMasqueradingVector[1]))
            {
                if (!validJsonOfField(1, pMasqueradingVector[1],
                                      pJson[pMasqueradingVector[1]], err, true))
                    return false;
            }
            else
            {
                err =
                    "The " + pMasqueradingVector[1] + " column cannot be null";
                return false;
            }
        }
        if (!pMasqueradingVector[2].empty())
        {
            if (pJson.isMember(pMasqueradingVector[2]))
            {
                if (!validJsonOfField(2, pMasqueradingVector[2],
                                      pJson[pMasqueradingVector[2]], err, true))
                    return false;
            }
            else
            {
                err =
                    "The " + pMasqueradingVector[2] + " column cannot be null";
                return false;
            }
        }
        if (!pMasqueradingVector[3].empty())
        {
            if (pJson.isMember(pMasqueradingVector[3]))
            {
                if (!validJsonOfField(3, pMasqueradingVector[3],
                                      pJson[pMasqueradingVector[3]], err, true))
                    return false;
            }
            else
            {
                err =
                    "The " + pMasqueradingVector[3] + " column cannot be null";
                return false;
            }
        }
        if (!pMasqueradingVector[4].empty())
        {
            if (pJson.isMember(pMasqueradingVector[4]))
            {
                if (!validJsonOfField(4, pMasqueradingVector[4],
                                      pJson[pMasqueradingVector[4]], err, true))
                    return false;
            }
        }
        if (!pMasqueradingVector[5].empty())
        {
            if (pJson.isMember(pMasqueradingVector[5]))
            {
                if (!validJsonOfField(5, pMasqueradingVector[5],
                                      pJson[pMasqueradingVector[5]], err, true))
                    return false;
            }
        }
        if (!pMasqueradingVector[6].empty())
        {
            if (pJson.isMember(pMasqueradingVector[6]))
            {
                if (!validJsonOfField(6, pMasqueradingVector[6],
                                      pJson[pMasqueradingVector[6]], err, true))
                    return false;
            }
        }
    }
    catch (const Json::LogicError& e)
    {
        err = e.what();
        return false;
    }
    return true;
}
bool Users::validateJsonForUpdate(const Json::Value& pJson, std::string& err)
{
    if (pJson.isMember("id"))
    {
        if (!validJsonOfField(0, "id", pJson["id"], err, false))
            return false;
    }
    else
    {
        err = "The value of primary key must be set in the json object for "
              "update";
        return false;
    }
    if (pJson.isMember("email"))
    {
        if (!validJsonOfField(1, "email", pJson["email"], err, false))
            return false;
    }
    if (pJson.isMember("password"))
    {
        if (!validJsonOfField(2, "password", pJson["password"], err, false))
            return false;
    }
    if (pJson.isMember("username"))
    {
        if (!validJsonOfField(3, "username", pJson["username"], err, false))
            return false;
    }
    if (pJson.isMember("pfp_url"))
    {
        if (!validJsonOfField(4, "pfp_url", pJson["pfp_url"], err, false))
            return false;
    }
    if (pJson.isMember("bio"))
    {
        if (!validJsonOfField(5, "bio", pJson["bio"], err, false))
            return false;
    }
    if (pJson.isMember("auth_code"))
    {
        if (!validJsonOfField(6, "auth_code", pJson["auth_code"], err, false))
            return false;
    }
    return true;
}
bool Users::validateMasqueradedJsonForUpdate(
    const Json::Value& pJson,
    const std::vector<std::string>& pMasqueradingVector, std::string& err)
{
    if (pMasqueradingVector.size() != 7)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try
    {
        if (!pMasqueradingVector[0].empty() &&
            pJson.isMember(pMasqueradingVector[0]))
        {
            if (!validJsonOfField(0, pMasqueradingVector[0],
                                  pJson[pMasqueradingVector[0]], err, false))
                return false;
        }
        else
        {
            err = "The value of primary key must be set in the json object for "
                  "update";
            return false;
        }
        if (!pMasqueradingVector[1].empty() &&
            pJson.isMember(pMasqueradingVector[1]))
        {
            if (!validJsonOfField(1, pMasqueradingVector[1],
                                  pJson[pMasqueradingVector[1]], err, false))
                return false;
        }
        if (!pMasqueradingVector[2].empty() &&
            pJson.isMember(pMasqueradingVector[2]))
        {
            if (!validJsonOfField(2, pMasqueradingVector[2],
                                  pJson[pMasqueradingVector[2]], err, false))
                return false;
        }
        if (!pMasqueradingVector[3].empty() &&
            pJson.isMember(pMasqueradingVector[3]))
        {
            if (!validJsonOfField(3, pMasqueradingVector[3],
                                  pJson[pMasqueradingVector[3]], err, false))
                return false;
        }
        if (!pMasqueradingVector[4].empty() &&
            pJson.isMember(pMasqueradingVector[4]))
        {
            if (!validJsonOfField(4, pMasqueradingVector[4],
                                  pJson[pMasqueradingVector[4]], err, false))
                return false;
        }
        if (!pMasqueradingVector[5].empty() &&
            pJson.isMember(pMasqueradingVector[5]))
        {
            if (!validJsonOfField(5, pMasqueradingVector[5],
                                  pJson[pMasqueradingVector[5]], err, false))
                return false;
        }
        if (!pMasqueradingVector[6].empty() &&
            pJson.isMember(pMasqueradingVector[6]))
        {
            if (!validJsonOfField(6, pMasqueradingVector[6],
                                  pJson[pMasqueradingVector[6]], err, false))
                return false;
        }
    }
    catch (const Json::LogicError& e)
    {
        err = e.what();
        return false;
    }
    return true;
}
bool Users::validJsonOfField(size_t index, const std::string& fieldName,
                             const Json::Value& pJson, std::string& err,
                             bool isForCreation)
{
    switch (index)
    {
    case 0:
        if (pJson.isNull())
        {
            err = "The " + fieldName + " column cannot be null";
            return false;
        }
        if (isForCreation)
        {
            err = "The automatic primary key cannot be set";
            return false;
        }
        if (!pJson.isUInt())
        {
            err = "Type error in the " + fieldName + " field";
            return false;
        }
        break;
    case 1:
        if (pJson.isNull())
        {
            err = "The " + fieldName + " column cannot be null";
            return false;
        }
        if (!pJson.isString())
        {
            err = "Type error in the " + fieldName + " field";
            return false;
        }
        break;
    case 2:
        if (pJson.isNull())
        {
            err = "The " + fieldName + " column cannot be null";
            return false;
        }
        if (!pJson.isString())
        {
            err = "Type error in the " + fieldName + " field";
            return false;
        }
        break;
    case 3:
        if (pJson.isNull())
        {
            err = "The " + fieldName + " column cannot be null";
            return false;
        }
        if (!pJson.isString())
        {
            err = "Type error in the " + fieldName + " field";
            return false;
        }
        break;
    case 4:
        if (pJson.isNull())
        {
            return true;
        }
        if (!pJson.isString())
        {
            err = "Type error in the " + fieldName + " field";
            return false;
        }
        break;
    case 5:
        if (pJson.isNull())
        {
            err = "The " + fieldName + " column cannot be null";
            return false;
        }
        if (!pJson.isString())
        {
            err = "Type error in the " + fieldName + " field";
            return false;
        }
        break;
    case 6:
        if (pJson.isNull())
        {
            return true;
        }
        if (!pJson.isString())
        {
            err = "Type error in the " + fieldName + " field";
            return false;
        }
        break;
    default:
        err = "Internal error in the server";
        return false;
    }
    return true;
}
std::vector<Events>
Users::getEvents(const drogon::orm::DbClientPtr& clientPtr) const
{
    std::shared_ptr<std::promise<std::vector<Events>>> pro(
        new std::promise<std::vector<Events>>);
    std::future<std::vector<Events>> f = pro->get_future();
    getEvents(
        clientPtr,
        [&pro](std::vector<Events> result)
        {
            try
            {
                pro->set_value(result);
            }
            catch (...)
            {
                pro->set_exception(std::current_exception());
            }
        },
        [&pro](const DrogonDbException& err)
        { pro->set_exception(std::make_exception_ptr(err)); });
    return f.get();
}
void Users::getEvents(const DbClientPtr& clientPtr,
                      const std::function<void(std::vector<Events>)>& rcb,
                      const ExceptionCallback& ecb) const
{
    const static std::string sql = "select * from events where author_id = ?";
    *clientPtr << sql << *id_ >> [rcb = std::move(rcb)](const Result& r)
    {
        std::vector<Events> ret;
        ret.reserve(r.size());
        for (const auto& row : r)
        {
            ret.emplace_back(Events(row));
        }
        rcb(ret);
    } >> ecb;
}
