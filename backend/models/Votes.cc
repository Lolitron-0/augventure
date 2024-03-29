/**
 *
 *  Votes.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "Votes.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::augventure_db;

const std::string Votes::Cols::_id = "id";
const std::string Votes::Cols::_suggestion_id = "suggestion_id";
const std::string Votes::Cols::_user_id = "user_id";
const std::string Votes::Cols::_vote_value = "vote_value";
const std::string Votes::primaryKeyName = "id";
const bool Votes::hasPrimaryKey = true;
const std::string Votes::tableName = "votes";

const std::vector<typename Votes::MetaData> Votes::metaData_={
{"id","uint32_t","int(10) unsigned",4,1,1,1},
{"suggestion_id","uint32_t","int(10) unsigned",4,0,0,1},
{"user_id","uint32_t","int(10) unsigned",4,0,0,1},
{"vote_value","int8_t","tinyint(4)",1,0,0,1}
};
const std::string &Votes::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Votes::Votes(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<uint32_t>(r["id"].as<uint32_t>());
        }
        if(!r["suggestion_id"].isNull())
        {
            suggestionId_=std::make_shared<uint32_t>(r["suggestion_id"].as<uint32_t>());
        }
        if(!r["user_id"].isNull())
        {
            userId_=std::make_shared<uint32_t>(r["user_id"].as<uint32_t>());
        }
        if(!r["vote_value"].isNull())
        {
            voteValue_=std::make_shared<int8_t>(r["vote_value"].as<int8_t>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 4 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
        index = offset + 0;
        if(!r[index].isNull())
        {
            id_=std::make_shared<uint32_t>(r[index].as<uint32_t>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            suggestionId_=std::make_shared<uint32_t>(r[index].as<uint32_t>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            userId_=std::make_shared<uint32_t>(r[index].as<uint32_t>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            voteValue_=std::make_shared<int8_t>(r[index].as<int8_t>());
        }
    }

}

Votes::Votes(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 4)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            id_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[0]].asUInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            suggestionId_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[1]].asUInt64());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            userId_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[2]].asUInt64());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            voteValue_=std::make_shared<int8_t>((int8_t)pJson[pMasqueradingVector[3]].asInt64());
        }
    }
}

Votes::Votes(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        dirtyFlag_[0]=true;
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<uint32_t>((uint32_t)pJson["id"].asUInt64());
        }
    }
    if(pJson.isMember("suggestion_id"))
    {
        dirtyFlag_[1]=true;
        if(!pJson["suggestion_id"].isNull())
        {
            suggestionId_=std::make_shared<uint32_t>((uint32_t)pJson["suggestion_id"].asUInt64());
        }
    }
    if(pJson.isMember("user_id"))
    {
        dirtyFlag_[2]=true;
        if(!pJson["user_id"].isNull())
        {
            userId_=std::make_shared<uint32_t>((uint32_t)pJson["user_id"].asUInt64());
        }
    }
    if(pJson.isMember("vote_value"))
    {
        dirtyFlag_[3]=true;
        if(!pJson["vote_value"].isNull())
        {
            voteValue_=std::make_shared<int8_t>((int8_t)pJson["vote_value"].asInt64());
        }
    }
}

void Votes::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 4)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            id_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[0]].asUInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            suggestionId_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[1]].asUInt64());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            userId_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[2]].asUInt64());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            voteValue_=std::make_shared<int8_t>((int8_t)pJson[pMasqueradingVector[3]].asInt64());
        }
    }
}

void Votes::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<uint32_t>((uint32_t)pJson["id"].asUInt64());
        }
    }
    if(pJson.isMember("suggestion_id"))
    {
        dirtyFlag_[1] = true;
        if(!pJson["suggestion_id"].isNull())
        {
            suggestionId_=std::make_shared<uint32_t>((uint32_t)pJson["suggestion_id"].asUInt64());
        }
    }
    if(pJson.isMember("user_id"))
    {
        dirtyFlag_[2] = true;
        if(!pJson["user_id"].isNull())
        {
            userId_=std::make_shared<uint32_t>((uint32_t)pJson["user_id"].asUInt64());
        }
    }
    if(pJson.isMember("vote_value"))
    {
        dirtyFlag_[3] = true;
        if(!pJson["vote_value"].isNull())
        {
            voteValue_=std::make_shared<int8_t>((int8_t)pJson["vote_value"].asInt64());
        }
    }
}

const uint32_t &Votes::getValueOfId() const noexcept
{
    const static uint32_t defaultValue = uint32_t();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<uint32_t> &Votes::getId() const noexcept
{
    return id_;
}
void Votes::setId(const uint32_t &pId) noexcept
{
    id_ = std::make_shared<uint32_t>(pId);
    dirtyFlag_[0] = true;
}
const typename Votes::PrimaryKeyType & Votes::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const uint32_t &Votes::getValueOfSuggestionId() const noexcept
{
    const static uint32_t defaultValue = uint32_t();
    if(suggestionId_)
        return *suggestionId_;
    return defaultValue;
}
const std::shared_ptr<uint32_t> &Votes::getSuggestionId() const noexcept
{
    return suggestionId_;
}
void Votes::setSuggestionId(const uint32_t &pSuggestionId) noexcept
{
    suggestionId_ = std::make_shared<uint32_t>(pSuggestionId);
    dirtyFlag_[1] = true;
}

const uint32_t &Votes::getValueOfUserId() const noexcept
{
    const static uint32_t defaultValue = uint32_t();
    if(userId_)
        return *userId_;
    return defaultValue;
}
const std::shared_ptr<uint32_t> &Votes::getUserId() const noexcept
{
    return userId_;
}
void Votes::setUserId(const uint32_t &pUserId) noexcept
{
    userId_ = std::make_shared<uint32_t>(pUserId);
    dirtyFlag_[2] = true;
}

const int8_t &Votes::getValueOfVoteValue() const noexcept
{
    const static int8_t defaultValue = int8_t();
    if(voteValue_)
        return *voteValue_;
    return defaultValue;
}
const std::shared_ptr<int8_t> &Votes::getVoteValue() const noexcept
{
    return voteValue_;
}
void Votes::setVoteValue(const int8_t &pVoteValue) noexcept
{
    voteValue_ = std::make_shared<int8_t>(pVoteValue);
    dirtyFlag_[3] = true;
}

void Votes::updateId(const uint64_t id)
{
    id_ = std::make_shared<uint32_t>(static_cast<uint32_t>(id));
}

const std::vector<std::string> &Votes::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "suggestion_id",
        "user_id",
        "vote_value"
    };
    return inCols;
}

void Votes::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getSuggestionId())
        {
            binder << getValueOfSuggestionId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getUserId())
        {
            binder << getValueOfUserId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getVoteValue())
        {
            binder << getValueOfVoteValue();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> Votes::updateColumns() const
{
    std::vector<std::string> ret;
    if(dirtyFlag_[1])
    {
        ret.push_back(getColumnName(1));
    }
    if(dirtyFlag_[2])
    {
        ret.push_back(getColumnName(2));
    }
    if(dirtyFlag_[3])
    {
        ret.push_back(getColumnName(3));
    }
    return ret;
}

void Votes::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getSuggestionId())
        {
            binder << getValueOfSuggestionId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getUserId())
        {
            binder << getValueOfUserId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getVoteValue())
        {
            binder << getValueOfVoteValue();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value Votes::toJson() const
{
    Json::Value ret;
    if(getId())
    {
        ret["id"]=getValueOfId();
    }
    else
    {
        ret["id"]=Json::Value();
    }
    if(getSuggestionId())
    {
        ret["suggestion_id"]=getValueOfSuggestionId();
    }
    else
    {
        ret["suggestion_id"]=Json::Value();
    }
    if(getUserId())
    {
        ret["user_id"]=getValueOfUserId();
    }
    else
    {
        ret["user_id"]=Json::Value();
    }
    if(getVoteValue())
    {
        ret["vote_value"]=getValueOfVoteValue();
    }
    else
    {
        ret["vote_value"]=Json::Value();
    }
    return ret;
}

Json::Value Votes::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 4)
    {
        if(!pMasqueradingVector[0].empty())
        {
            if(getId())
            {
                ret[pMasqueradingVector[0]]=getValueOfId();
            }
            else
            {
                ret[pMasqueradingVector[0]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[1].empty())
        {
            if(getSuggestionId())
            {
                ret[pMasqueradingVector[1]]=getValueOfSuggestionId();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getUserId())
            {
                ret[pMasqueradingVector[2]]=getValueOfUserId();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[3].empty())
        {
            if(getVoteValue())
            {
                ret[pMasqueradingVector[3]]=getValueOfVoteValue();
            }
            else
            {
                ret[pMasqueradingVector[3]]=Json::Value();
            }
        }
        return ret;
    }
    LOG_ERROR << "Masquerade failed";
    if(getId())
    {
        ret["id"]=getValueOfId();
    }
    else
    {
        ret["id"]=Json::Value();
    }
    if(getSuggestionId())
    {
        ret["suggestion_id"]=getValueOfSuggestionId();
    }
    else
    {
        ret["suggestion_id"]=Json::Value();
    }
    if(getUserId())
    {
        ret["user_id"]=getValueOfUserId();
    }
    else
    {
        ret["user_id"]=Json::Value();
    }
    if(getVoteValue())
    {
        ret["vote_value"]=getValueOfVoteValue();
    }
    else
    {
        ret["vote_value"]=Json::Value();
    }
    return ret;
}

bool Votes::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, true))
            return false;
    }
    if(pJson.isMember("suggestion_id"))
    {
        if(!validJsonOfField(1, "suggestion_id", pJson["suggestion_id"], err, true))
            return false;
    }
    else
    {
        err="The suggestion_id column cannot be null";
        return false;
    }
    if(pJson.isMember("user_id"))
    {
        if(!validJsonOfField(2, "user_id", pJson["user_id"], err, true))
            return false;
    }
    else
    {
        err="The user_id column cannot be null";
        return false;
    }
    if(pJson.isMember("vote_value"))
    {
        if(!validJsonOfField(3, "vote_value", pJson["vote_value"], err, true))
            return false;
    }
    else
    {
        err="The vote_value column cannot be null";
        return false;
    }
    return true;
}
bool Votes::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                               const std::vector<std::string> &pMasqueradingVector,
                                               std::string &err)
{
    if(pMasqueradingVector.size() != 4)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
      if(!pMasqueradingVector[0].empty())
      {
          if(pJson.isMember(pMasqueradingVector[0]))
          {
              if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[1].empty())
      {
          if(pJson.isMember(pMasqueradingVector[1]))
          {
              if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, true))
                  return false;
          }
        else
        {
            err="The " + pMasqueradingVector[1] + " column cannot be null";
            return false;
        }
      }
      if(!pMasqueradingVector[2].empty())
      {
          if(pJson.isMember(pMasqueradingVector[2]))
          {
              if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, true))
                  return false;
          }
        else
        {
            err="The " + pMasqueradingVector[2] + " column cannot be null";
            return false;
        }
      }
      if(!pMasqueradingVector[3].empty())
      {
          if(pJson.isMember(pMasqueradingVector[3]))
          {
              if(!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, true))
                  return false;
          }
        else
        {
            err="The " + pMasqueradingVector[3] + " column cannot be null";
            return false;
        }
      }
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool Votes::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, false))
            return false;
    }
    else
    {
        err = "The value of primary key must be set in the json object for update";
        return false;
    }
    if(pJson.isMember("suggestion_id"))
    {
        if(!validJsonOfField(1, "suggestion_id", pJson["suggestion_id"], err, false))
            return false;
    }
    if(pJson.isMember("user_id"))
    {
        if(!validJsonOfField(2, "user_id", pJson["user_id"], err, false))
            return false;
    }
    if(pJson.isMember("vote_value"))
    {
        if(!validJsonOfField(3, "vote_value", pJson["vote_value"], err, false))
            return false;
    }
    return true;
}
bool Votes::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                             const std::vector<std::string> &pMasqueradingVector,
                                             std::string &err)
{
    if(pMasqueradingVector.size() != 4)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
      if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
      {
          if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, false))
              return false;
      }
    else
    {
        err = "The value of primary key must be set in the json object for update";
        return false;
    }
      if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
      {
          if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, false))
              return false;
      }
      if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
      {
          if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, false))
              return false;
      }
      if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
      {
          if(!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, false))
              return false;
      }
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool Votes::validJsonOfField(size_t index,
                             const std::string &fieldName,
                             const Json::Value &pJson,
                             std::string &err,
                             bool isForCreation)
{
    switch(index)
    {
        case 0:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(isForCreation)
            {
                err="The automatic primary key cannot be set";
                return false;
            }
            if(!pJson.isUInt())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 1:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isUInt())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 2:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isUInt())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 3:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isInt())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        default:
            err="Internal error in the server";
            return false;
    }
    return true;
}
