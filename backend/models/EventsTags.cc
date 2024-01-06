/**
 *
 *  EventsTags.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "EventsTags.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::augventure_db;

const std::string EventsTags::Cols::_event_id = "event_id";
const std::string EventsTags::Cols::_tag_id = "tag_id";
const std::string EventsTags::primaryKeyName = "";
const bool EventsTags::hasPrimaryKey = false;
const std::string EventsTags::tableName = "events_tags";

const std::vector<typename EventsTags::MetaData> EventsTags::metaData_={
{"event_id","uint32_t","int(10) unsigned",4,0,0,1},
{"tag_id","uint32_t","int(10) unsigned",4,0,0,1}
};
const std::string &EventsTags::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
EventsTags::EventsTags(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["event_id"].isNull())
        {
            eventId_=std::make_shared<uint32_t>(r["event_id"].as<uint32_t>());
        }
        if(!r["tag_id"].isNull())
        {
            tagId_=std::make_shared<uint32_t>(r["tag_id"].as<uint32_t>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 2 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
        index = offset + 0;
        if(!r[index].isNull())
        {
            eventId_=std::make_shared<uint32_t>(r[index].as<uint32_t>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            tagId_=std::make_shared<uint32_t>(r[index].as<uint32_t>());
        }
    }

}

EventsTags::EventsTags(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 2)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            eventId_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[0]].asUInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            tagId_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[1]].asUInt64());
        }
    }
}

EventsTags::EventsTags(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("event_id"))
    {
        dirtyFlag_[0]=true;
        if(!pJson["event_id"].isNull())
        {
            eventId_=std::make_shared<uint32_t>((uint32_t)pJson["event_id"].asUInt64());
        }
    }
    if(pJson.isMember("tag_id"))
    {
        dirtyFlag_[1]=true;
        if(!pJson["tag_id"].isNull())
        {
            tagId_=std::make_shared<uint32_t>((uint32_t)pJson["tag_id"].asUInt64());
        }
    }
}

void EventsTags::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 2)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            eventId_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[0]].asUInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            tagId_=std::make_shared<uint32_t>((uint32_t)pJson[pMasqueradingVector[1]].asUInt64());
        }
    }
}

void EventsTags::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("event_id"))
    {
        dirtyFlag_[0] = true;
        if(!pJson["event_id"].isNull())
        {
            eventId_=std::make_shared<uint32_t>((uint32_t)pJson["event_id"].asUInt64());
        }
    }
    if(pJson.isMember("tag_id"))
    {
        dirtyFlag_[1] = true;
        if(!pJson["tag_id"].isNull())
        {
            tagId_=std::make_shared<uint32_t>((uint32_t)pJson["tag_id"].asUInt64());
        }
    }
}

const uint32_t &EventsTags::getValueOfEventId() const noexcept
{
    const static uint32_t defaultValue = uint32_t();
    if(eventId_)
        return *eventId_;
    return defaultValue;
}
const std::shared_ptr<uint32_t> &EventsTags::getEventId() const noexcept
{
    return eventId_;
}
void EventsTags::setEventId(const uint32_t &pEventId) noexcept
{
    eventId_ = std::make_shared<uint32_t>(pEventId);
    dirtyFlag_[0] = true;
}

const uint32_t &EventsTags::getValueOfTagId() const noexcept
{
    const static uint32_t defaultValue = uint32_t();
    if(tagId_)
        return *tagId_;
    return defaultValue;
}
const std::shared_ptr<uint32_t> &EventsTags::getTagId() const noexcept
{
    return tagId_;
}
void EventsTags::setTagId(const uint32_t &pTagId) noexcept
{
    tagId_ = std::make_shared<uint32_t>(pTagId);
    dirtyFlag_[1] = true;
}

void EventsTags::updateId(const uint64_t id)
{
}

const std::vector<std::string> &EventsTags::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "event_id",
        "tag_id"
    };
    return inCols;
}

void EventsTags::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[0])
    {
        if(getEventId())
        {
            binder << getValueOfEventId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[1])
    {
        if(getTagId())
        {
            binder << getValueOfTagId();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> EventsTags::updateColumns() const
{
    std::vector<std::string> ret;
    if(dirtyFlag_[0])
    {
        ret.push_back(getColumnName(0));
    }
    if(dirtyFlag_[1])
    {
        ret.push_back(getColumnName(1));
    }
    return ret;
}

void EventsTags::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[0])
    {
        if(getEventId())
        {
            binder << getValueOfEventId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[1])
    {
        if(getTagId())
        {
            binder << getValueOfTagId();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value EventsTags::toJson() const
{
    Json::Value ret;
    if(getEventId())
    {
        ret["event_id"]=getValueOfEventId();
    }
    else
    {
        ret["event_id"]=Json::Value();
    }
    if(getTagId())
    {
        ret["tag_id"]=getValueOfTagId();
    }
    else
    {
        ret["tag_id"]=Json::Value();
    }
    return ret;
}

Json::Value EventsTags::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 2)
    {
        if(!pMasqueradingVector[0].empty())
        {
            if(getEventId())
            {
                ret[pMasqueradingVector[0]]=getValueOfEventId();
            }
            else
            {
                ret[pMasqueradingVector[0]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[1].empty())
        {
            if(getTagId())
            {
                ret[pMasqueradingVector[1]]=getValueOfTagId();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        return ret;
    }
    LOG_ERROR << "Masquerade failed";
    if(getEventId())
    {
        ret["event_id"]=getValueOfEventId();
    }
    else
    {
        ret["event_id"]=Json::Value();
    }
    if(getTagId())
    {
        ret["tag_id"]=getValueOfTagId();
    }
    else
    {
        ret["tag_id"]=Json::Value();
    }
    return ret;
}

bool EventsTags::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("event_id"))
    {
        if(!validJsonOfField(0, "event_id", pJson["event_id"], err, true))
            return false;
    }
    else
    {
        err="The event_id column cannot be null";
        return false;
    }
    if(pJson.isMember("tag_id"))
    {
        if(!validJsonOfField(1, "tag_id", pJson["tag_id"], err, true))
            return false;
    }
    else
    {
        err="The tag_id column cannot be null";
        return false;
    }
    return true;
}
bool EventsTags::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                                    const std::vector<std::string> &pMasqueradingVector,
                                                    std::string &err)
{
    if(pMasqueradingVector.size() != 2)
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
        else
        {
            err="The " + pMasqueradingVector[0] + " column cannot be null";
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
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool EventsTags::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("event_id"))
    {
        if(!validJsonOfField(0, "event_id", pJson["event_id"], err, false))
            return false;
    }
    if(pJson.isMember("tag_id"))
    {
        if(!validJsonOfField(1, "tag_id", pJson["tag_id"], err, false))
            return false;
    }
    return true;
}
bool EventsTags::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                                  const std::vector<std::string> &pMasqueradingVector,
                                                  std::string &err)
{
    if(pMasqueradingVector.size() != 2)
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
      if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
      {
          if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, false))
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
bool EventsTags::validJsonOfField(size_t index,
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
        default:
            err="Internal error in the server";
            return false;
    }
    return true;
}
