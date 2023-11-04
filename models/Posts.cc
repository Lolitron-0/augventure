/**
 *
 *  Posts.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "Posts.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::augventure_db;

const std::string Posts::Cols::_id = "id";
const std::string Posts::Cols::_text_content = "text_content";
const std::string Posts::Cols::_suggestion_id = "suggestion_id";
const std::string Posts::Cols::_sprint_id = "sprint_id";
const std::string Posts::primaryKeyName = "id";
const bool Posts::hasPrimaryKey = true;
const std::string Posts::tableName = "posts";

const std::vector<typename Posts::MetaData> Posts::metaData_={
{"id","uint32_t","int(10) unsigned",4,1,1,1},
{"text_content","std::string","text",0,0,0,0},
{"suggestion_id","uint32_t","int(10) unsigned",4,0,0,0},
{"sprint_id","uint32_t","int(10) unsigned",4,0,0,0}
};
const std::string &Posts::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Posts::Posts(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<uint32_t>(r["id"].as<uint32_t>());
        }
        if(!r["text_content"].isNull())
        {
            textContent_=std::make_shared<std::string>(r["text_content"].as<std::string>());
        }
        if(!r["suggestion_id"].isNull())
        {
            suggestionId_=std::make_shared<uint32_t>(r["suggestion_id"].as<uint32_t>());
        }
        if(!r["sprint_id"].isNull())
        {
            sprintId_=std::make_shared<uint32_t>(r["sprint_id"].as<uint32_t>());
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
            textContent_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            suggestionId_=std::make_shared<uint32_t>(r[index].as<uint32_t>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            sprintId_=std::make_shared<uint32_t>(r[index].as<uint32_t>());
        }
    }

}

Posts::Posts(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
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
            textContent_=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            suggestionId_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[2]].asUInt64());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            sprintId_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[3]].asUInt64());
        }
    }
}

Posts::Posts(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        dirtyFlag_[0]=true;
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<uint32_t>((uint32_t)pJson["id"].asUInt64());
        }
    }
    if(pJson.isMember("text_content"))
    {
        dirtyFlag_[1]=true;
        if(!pJson["text_content"].isNull())
        {
            textContent_=std::make_shared<std::string>(pJson["text_content"].asString());
        }
    }
    if(pJson.isMember("suggestion_id"))
    {
        dirtyFlag_[2]=true;
        if(!pJson["suggestion_id"].isNull())
        {
            suggestionId_=std::make_shared<uint32_t>((uint32_t)pJson["suggestion_id"].asUInt64());
        }
    }
    if(pJson.isMember("sprint_id"))
    {
        dirtyFlag_[3]=true;
        if(!pJson["sprint_id"].isNull())
        {
            sprintId_=std::make_shared<uint32_t>((uint32_t)pJson["sprint_id"].asUInt64());
        }
    }
}

void Posts::updateByMasqueradedJson(const Json::Value &pJson,
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
            textContent_=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            suggestionId_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[2]].asUInt64());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            sprintId_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[3]].asUInt64());
        }
    }
}

void Posts::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<uint32_t>((uint32_t)pJson["id"].asUInt64());
        }
    }
    if(pJson.isMember("text_content"))
    {
        dirtyFlag_[1] = true;
        if(!pJson["text_content"].isNull())
        {
            textContent_=std::make_shared<std::string>(pJson["text_content"].asString());
        }
    }
    if(pJson.isMember("suggestion_id"))
    {
        dirtyFlag_[2] = true;
        if(!pJson["suggestion_id"].isNull())
        {
            suggestionId_=std::make_shared<uint32_t>((uint32_t)pJson["suggestion_id"].asUInt64());
        }
    }
    if(pJson.isMember("sprint_id"))
    {
        dirtyFlag_[3] = true;
        if(!pJson["sprint_id"].isNull())
        {
            sprintId_=std::make_shared<uint32_t>((uint32_t)pJson["sprint_id"].asUInt64());
        }
    }
}

const uint32_t &Posts::getValueOfId() const noexcept
{
    const static uint32_t defaultValue = uint32_t();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<uint32_t> &Posts::getId() const noexcept
{
    return id_;
}
void Posts::setId(const uint32_t &pId) noexcept
{
    id_ = std::make_shared<uint32_t>(pId);
    dirtyFlag_[0] = true;
}
const typename Posts::PrimaryKeyType & Posts::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &Posts::getValueOfTextContent() const noexcept
{
    const static std::string defaultValue = std::string();
    if(textContent_)
        return *textContent_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Posts::getTextContent() const noexcept
{
    return textContent_;
}
void Posts::setTextContent(const std::string &pTextContent) noexcept
{
    textContent_ = std::make_shared<std::string>(pTextContent);
    dirtyFlag_[1] = true;
}
void Posts::setTextContent(std::string &&pTextContent) noexcept
{
    textContent_ = std::make_shared<std::string>(std::move(pTextContent));
    dirtyFlag_[1] = true;
}
void Posts::setTextContentToNull() noexcept
{
    textContent_.reset();
    dirtyFlag_[1] = true;
}

const uint32_t &Posts::getValueOfSuggestionId() const noexcept
{
    const static uint32_t defaultValue = uint32_t();
    if(suggestionId_)
        return *suggestionId_;
    return defaultValue;
}
const std::shared_ptr<uint32_t> &Posts::getSuggestionId() const noexcept
{
    return suggestionId_;
}
void Posts::setSuggestionId(const uint32_t &pSuggestionId) noexcept
{
    suggestionId_ = std::make_shared<uint32_t>(pSuggestionId);
    dirtyFlag_[2] = true;
}
void Posts::setSuggestionIdToNull() noexcept
{
    suggestionId_.reset();
    dirtyFlag_[2] = true;
}

const uint32_t &Posts::getValueOfSprintId() const noexcept
{
    const static uint32_t defaultValue = uint32_t();
    if(sprintId_)
        return *sprintId_;
    return defaultValue;
}
const std::shared_ptr<uint32_t> &Posts::getSprintId() const noexcept
{
    return sprintId_;
}
void Posts::setSprintId(const uint32_t &pSprintId) noexcept
{
    sprintId_ = std::make_shared<uint32_t>(pSprintId);
    dirtyFlag_[3] = true;
}
void Posts::setSprintIdToNull() noexcept
{
    sprintId_.reset();
    dirtyFlag_[3] = true;
}

void Posts::updateId(const uint64_t id)
{
    id_ = std::make_shared<uint32_t>(static_cast<uint32_t>(id));
}

const std::vector<std::string> &Posts::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "text_content",
        "suggestion_id",
        "sprint_id"
    };
    return inCols;
}

void Posts::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getTextContent())
        {
            binder << getValueOfTextContent();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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
    if(dirtyFlag_[3])
    {
        if(getSprintId())
        {
            binder << getValueOfSprintId();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> Posts::updateColumns() const
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

void Posts::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getTextContent())
        {
            binder << getValueOfTextContent();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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
    if(dirtyFlag_[3])
    {
        if(getSprintId())
        {
            binder << getValueOfSprintId();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value Posts::toJson() const
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
    if(getTextContent())
    {
        ret["text_content"]=getValueOfTextContent();
    }
    else
    {
        ret["text_content"]=Json::Value();
    }
    if(getSuggestionId())
    {
        ret["suggestion_id"]=getValueOfSuggestionId();
    }
    else
    {
        ret["suggestion_id"]=Json::Value();
    }
    if(getSprintId())
    {
        ret["sprint_id"]=getValueOfSprintId();
    }
    else
    {
        ret["sprint_id"]=Json::Value();
    }
    return ret;
}

Json::Value Posts::toMasqueradedJson(
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
            if(getTextContent())
            {
                ret[pMasqueradingVector[1]]=getValueOfTextContent();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getSuggestionId())
            {
                ret[pMasqueradingVector[2]]=getValueOfSuggestionId();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[3].empty())
        {
            if(getSprintId())
            {
                ret[pMasqueradingVector[3]]=getValueOfSprintId();
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
    if(getTextContent())
    {
        ret["text_content"]=getValueOfTextContent();
    }
    else
    {
        ret["text_content"]=Json::Value();
    }
    if(getSuggestionId())
    {
        ret["suggestion_id"]=getValueOfSuggestionId();
    }
    else
    {
        ret["suggestion_id"]=Json::Value();
    }
    if(getSprintId())
    {
        ret["sprint_id"]=getValueOfSprintId();
    }
    else
    {
        ret["sprint_id"]=Json::Value();
    }
    return ret;
}

bool Posts::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, true))
            return false;
    }
    if(pJson.isMember("text_content"))
    {
        if(!validJsonOfField(1, "text_content", pJson["text_content"], err, true))
            return false;
    }
    if(pJson.isMember("suggestion_id"))
    {
        if(!validJsonOfField(2, "suggestion_id", pJson["suggestion_id"], err, true))
            return false;
    }
    if(pJson.isMember("sprint_id"))
    {
        if(!validJsonOfField(3, "sprint_id", pJson["sprint_id"], err, true))
            return false;
    }
    return true;
}
bool Posts::validateMasqueradedJsonForCreation(const Json::Value &pJson,
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
      }
      if(!pMasqueradingVector[2].empty())
      {
          if(pJson.isMember(pMasqueradingVector[2]))
          {
              if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, true))
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
      }
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool Posts::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
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
    if(pJson.isMember("text_content"))
    {
        if(!validJsonOfField(1, "text_content", pJson["text_content"], err, false))
            return false;
    }
    if(pJson.isMember("suggestion_id"))
    {
        if(!validJsonOfField(2, "suggestion_id", pJson["suggestion_id"], err, false))
            return false;
    }
    if(pJson.isMember("sprint_id"))
    {
        if(!validJsonOfField(3, "sprint_id", pJson["sprint_id"], err, false))
            return false;
    }
    return true;
}
bool Posts::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
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
bool Posts::validJsonOfField(size_t index,
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
                return true;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 2:
            if(pJson.isNull())
            {
                return true;
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
                return true;
            }
            if(!pJson.isUInt())
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
