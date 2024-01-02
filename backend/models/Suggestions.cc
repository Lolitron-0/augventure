/**
 *
 *  Suggestions.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "Suggestions.h"
#include "Posts.h"
#include "Sprints.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::augventure_db;

const std::string Suggestions::Cols::_id = "id";
const std::string Suggestions::Cols::_author_id = "author_id";
const std::string Suggestions::Cols::_post_date = "post_date";
const std::string Suggestions::Cols::_sprint_id = "sprint_id";
const std::string Suggestions::Cols::_votes = "votes";
const std::string Suggestions::primaryKeyName = "id";
const bool Suggestions::hasPrimaryKey = true;
const std::string Suggestions::tableName = "suggestions";

const std::vector<typename Suggestions::MetaData> Suggestions::metaData_={
{"id","uint32_t","int(10) unsigned",4,1,1,1},
{"author_id","uint32_t","int(10) unsigned",4,0,0,1},
{"post_date","::trantor::Date","datetime",0,0,0,1},
{"sprint_id","uint32_t","int(10) unsigned",4,0,0,1},
{"votes","int32_t","int(11)",4,0,0,1}
};
const std::string &Suggestions::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Suggestions::Suggestions(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<uint32_t>(r["id"].as<uint32_t>());
        }
        if(!r["author_id"].isNull())
        {
            authorId_=std::make_shared<uint32_t>(r["author_id"].as<uint32_t>());
        }
        if(!r["post_date"].isNull())
        {
            auto timeStr = r["post_date"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                postDate_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        if(!r["sprint_id"].isNull())
        {
            sprintId_=std::make_shared<uint32_t>(r["sprint_id"].as<uint32_t>());
        }
        if(!r["votes"].isNull())
        {
            votes_=std::make_shared<int32_t>(r["votes"].as<int32_t>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 5 > r.size())
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
            authorId_=std::make_shared<uint32_t>(r[index].as<uint32_t>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            auto timeStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                postDate_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            sprintId_=std::make_shared<uint32_t>(r[index].as<uint32_t>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            votes_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
    }

}

Suggestions::Suggestions(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 5)
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
            authorId_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[1]].asUInt64());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            auto timeStr = pJson[pMasqueradingVector[2]].asString();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                postDate_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
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
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            votes_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[4]].asInt64());
        }
    }
}

Suggestions::Suggestions(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        dirtyFlag_[0]=true;
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<uint32_t>((uint32_t)pJson["id"].asUInt64());
        }
    }
    if(pJson.isMember("author_id"))
    {
        dirtyFlag_[1]=true;
        if(!pJson["author_id"].isNull())
        {
            authorId_=std::make_shared<uint32_t>((uint32_t)pJson["author_id"].asUInt64());
        }
    }
    if(pJson.isMember("post_date"))
    {
        dirtyFlag_[2]=true;
        if(!pJson["post_date"].isNull())
        {
            auto timeStr = pJson["post_date"].asString();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                postDate_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
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
    if(pJson.isMember("votes"))
    {
        dirtyFlag_[4]=true;
        if(!pJson["votes"].isNull())
        {
            votes_=std::make_shared<int32_t>((int32_t)pJson["votes"].asInt64());
        }
    }
}

void Suggestions::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 5)
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
            authorId_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[1]].asUInt64());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            auto timeStr = pJson[pMasqueradingVector[2]].asString();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                postDate_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
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
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            votes_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[4]].asInt64());
        }
    }
}

void Suggestions::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<uint32_t>((uint32_t)pJson["id"].asUInt64());
        }
    }
    if(pJson.isMember("author_id"))
    {
        dirtyFlag_[1] = true;
        if(!pJson["author_id"].isNull())
        {
            authorId_=std::make_shared<uint32_t>((uint32_t)pJson["author_id"].asUInt64());
        }
    }
    if(pJson.isMember("post_date"))
    {
        dirtyFlag_[2] = true;
        if(!pJson["post_date"].isNull())
        {
            auto timeStr = pJson["post_date"].asString();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                postDate_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
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
    if(pJson.isMember("votes"))
    {
        dirtyFlag_[4] = true;
        if(!pJson["votes"].isNull())
        {
            votes_=std::make_shared<int32_t>((int32_t)pJson["votes"].asInt64());
        }
    }
}

const uint32_t &Suggestions::getValueOfId() const noexcept
{
    const static uint32_t defaultValue = uint32_t();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<uint32_t> &Suggestions::getId() const noexcept
{
    return id_;
}
void Suggestions::setId(const uint32_t &pId) noexcept
{
    id_ = std::make_shared<uint32_t>(pId);
    dirtyFlag_[0] = true;
}
const typename Suggestions::PrimaryKeyType & Suggestions::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const uint32_t &Suggestions::getValueOfAuthorId() const noexcept
{
    const static uint32_t defaultValue = uint32_t();
    if(authorId_)
        return *authorId_;
    return defaultValue;
}
const std::shared_ptr<uint32_t> &Suggestions::getAuthorId() const noexcept
{
    return authorId_;
}
void Suggestions::setAuthorId(const uint32_t &pAuthorId) noexcept
{
    authorId_ = std::make_shared<uint32_t>(pAuthorId);
    dirtyFlag_[1] = true;
}

const ::trantor::Date &Suggestions::getValueOfPostDate() const noexcept
{
    const static ::trantor::Date defaultValue = ::trantor::Date();
    if(postDate_)
        return *postDate_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Suggestions::getPostDate() const noexcept
{
    return postDate_;
}
void Suggestions::setPostDate(const ::trantor::Date &pPostDate) noexcept
{
    postDate_ = std::make_shared<::trantor::Date>(pPostDate);
    dirtyFlag_[2] = true;
}

const uint32_t &Suggestions::getValueOfSprintId() const noexcept
{
    const static uint32_t defaultValue = uint32_t();
    if(sprintId_)
        return *sprintId_;
    return defaultValue;
}
const std::shared_ptr<uint32_t> &Suggestions::getSprintId() const noexcept
{
    return sprintId_;
}
void Suggestions::setSprintId(const uint32_t &pSprintId) noexcept
{
    sprintId_ = std::make_shared<uint32_t>(pSprintId);
    dirtyFlag_[3] = true;
}

const int32_t &Suggestions::getValueOfVotes() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(votes_)
        return *votes_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Suggestions::getVotes() const noexcept
{
    return votes_;
}
void Suggestions::setVotes(const int32_t &pVotes) noexcept
{
    votes_ = std::make_shared<int32_t>(pVotes);
    dirtyFlag_[4] = true;
}

void Suggestions::updateId(const uint64_t id)
{
    id_ = std::make_shared<uint32_t>(static_cast<uint32_t>(id));
}

const std::vector<std::string> &Suggestions::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "author_id",
        "post_date",
        "sprint_id",
        "votes"
    };
    return inCols;
}

void Suggestions::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getAuthorId())
        {
            binder << getValueOfAuthorId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getPostDate())
        {
            binder << getValueOfPostDate();
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
    if(dirtyFlag_[4])
    {
        if(getVotes())
        {
            binder << getValueOfVotes();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> Suggestions::updateColumns() const
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
    if(dirtyFlag_[4])
    {
        ret.push_back(getColumnName(4));
    }
    return ret;
}

void Suggestions::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getAuthorId())
        {
            binder << getValueOfAuthorId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getPostDate())
        {
            binder << getValueOfPostDate();
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
    if(dirtyFlag_[4])
    {
        if(getVotes())
        {
            binder << getValueOfVotes();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value Suggestions::toJson() const
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
    if(getAuthorId())
    {
        ret["author_id"]=getValueOfAuthorId();
    }
    else
    {
        ret["author_id"]=Json::Value();
    }
    if(getPostDate())
    {
        ret["post_date"]=getPostDate()->toDbStringLocal();
    }
    else
    {
        ret["post_date"]=Json::Value();
    }
    if(getSprintId())
    {
        ret["sprint_id"]=getValueOfSprintId();
    }
    else
    {
        ret["sprint_id"]=Json::Value();
    }
    if(getVotes())
    {
        ret["votes"]=getValueOfVotes();
    }
    else
    {
        ret["votes"]=Json::Value();
    }
    return ret;
}

Json::Value Suggestions::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 5)
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
            if(getAuthorId())
            {
                ret[pMasqueradingVector[1]]=getValueOfAuthorId();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getPostDate())
            {
                ret[pMasqueradingVector[2]]=getPostDate()->toDbStringLocal();
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
        if(!pMasqueradingVector[4].empty())
        {
            if(getVotes())
            {
                ret[pMasqueradingVector[4]]=getValueOfVotes();
            }
            else
            {
                ret[pMasqueradingVector[4]]=Json::Value();
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
    if(getAuthorId())
    {
        ret["author_id"]=getValueOfAuthorId();
    }
    else
    {
        ret["author_id"]=Json::Value();
    }
    if(getPostDate())
    {
        ret["post_date"]=getPostDate()->toDbStringLocal();
    }
    else
    {
        ret["post_date"]=Json::Value();
    }
    if(getSprintId())
    {
        ret["sprint_id"]=getValueOfSprintId();
    }
    else
    {
        ret["sprint_id"]=Json::Value();
    }
    if(getVotes())
    {
        ret["votes"]=getValueOfVotes();
    }
    else
    {
        ret["votes"]=Json::Value();
    }
    return ret;
}

bool Suggestions::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, true))
            return false;
    }
    if(pJson.isMember("author_id"))
    {
        if(!validJsonOfField(1, "author_id", pJson["author_id"], err, true))
            return false;
    }
    else
    {
        err="The author_id column cannot be null";
        return false;
    }
    if(pJson.isMember("post_date"))
    {
        if(!validJsonOfField(2, "post_date", pJson["post_date"], err, true))
            return false;
    }
    if(pJson.isMember("sprint_id"))
    {
        if(!validJsonOfField(3, "sprint_id", pJson["sprint_id"], err, true))
            return false;
    }
    else
    {
        err="The sprint_id column cannot be null";
        return false;
    }
    if(pJson.isMember("votes"))
    {
        if(!validJsonOfField(4, "votes", pJson["votes"], err, true))
            return false;
    }
    return true;
}
bool Suggestions::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                                     const std::vector<std::string> &pMasqueradingVector,
                                                     std::string &err)
{
    if(pMasqueradingVector.size() != 5)
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
      if(!pMasqueradingVector[4].empty())
      {
          if(pJson.isMember(pMasqueradingVector[4]))
          {
              if(!validJsonOfField(4, pMasqueradingVector[4], pJson[pMasqueradingVector[4]], err, true))
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
bool Suggestions::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
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
    if(pJson.isMember("author_id"))
    {
        if(!validJsonOfField(1, "author_id", pJson["author_id"], err, false))
            return false;
    }
    if(pJson.isMember("post_date"))
    {
        if(!validJsonOfField(2, "post_date", pJson["post_date"], err, false))
            return false;
    }
    if(pJson.isMember("sprint_id"))
    {
        if(!validJsonOfField(3, "sprint_id", pJson["sprint_id"], err, false))
            return false;
    }
    if(pJson.isMember("votes"))
    {
        if(!validJsonOfField(4, "votes", pJson["votes"], err, false))
            return false;
    }
    return true;
}
bool Suggestions::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                                   const std::vector<std::string> &pMasqueradingVector,
                                                   std::string &err)
{
    if(pMasqueradingVector.size() != 5)
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
      if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
      {
          if(!validJsonOfField(4, pMasqueradingVector[4], pJson[pMasqueradingVector[4]], err, false))
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
bool Suggestions::validJsonOfField(size_t index,
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
            if(!pJson.isString())
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
            if(!pJson.isUInt())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 4:
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

Posts Suggestions::getPost(const drogon::orm::DbClientPtr &clientPtr) const {
    std::shared_ptr<std::promise<Posts>> pro(new std::promise<Posts>);
    std::future<Posts> f = pro->get_future();
    getPost(clientPtr, [&pro] (Posts result) {
        try {
            pro->set_value(result);
        }
        catch (...) {
            pro->set_exception(std::current_exception());
        }
    }, [&pro] (const DrogonDbException &err) {
        pro->set_exception(std::make_exception_ptr(err));
    });
    return f.get();
}
void Suggestions::getPost(const DbClientPtr &clientPtr,
                          const std::function<void(Posts)> &rcb,
                          const ExceptionCallback &ecb) const
{
    const static std::string sql = "select * from posts where suggestion_id = ?";
    *clientPtr << sql
               << *id_
               >> [rcb = std::move(rcb), ecb](const Result &r){
                    if (r.size() == 0)
                    {
                        ecb(UnexpectedRows("0 rows found"));
                    }
                    else if (r.size() > 1)
                    {
                        ecb(UnexpectedRows("Found more than one row"));
                    }
                    else
                    {
                        rcb(Posts(r[0]));
                    }
               }
               >> ecb;
}

Sprints Suggestions::getSprint(const drogon::orm::DbClientPtr &clientPtr) const {
    std::shared_ptr<std::promise<Sprints>> pro(new std::promise<Sprints>);
    std::future<Sprints> f = pro->get_future();
    getSprint(clientPtr, [&pro] (Sprints result) {
        try {
            pro->set_value(result);
        }
        catch (...) {
            pro->set_exception(std::current_exception());
        }
    }, [&pro] (const DrogonDbException &err) {
        pro->set_exception(std::make_exception_ptr(err));
    });
    return f.get();
}
void Suggestions::getSprint(const DbClientPtr &clientPtr,
                            const std::function<void(Sprints)> &rcb,
                            const ExceptionCallback &ecb) const
{
    const static std::string sql = "select * from sprints where id = ?";
    *clientPtr << sql
               << *sprintId_
               >> [rcb = std::move(rcb), ecb](const Result &r){
                    if (r.size() == 0)
                    {
                        ecb(UnexpectedRows("0 rows found"));
                    }
                    else if (r.size() > 1)
                    {
                        ecb(UnexpectedRows("Found more than one row"));
                    }
                    else
                    {
                        rcb(Sprints(r[0]));
                    }
               }
               >> ecb;
}
