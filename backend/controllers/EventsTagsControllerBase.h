/**
 *
 *  EventsTagsControllerBase.h
 *  DO NOT EDIT. This file is generated by drogon_ctl automatically.
 *  Users should implement business logic in the derived class.
 */

#pragma once

#include <drogon/HttpController.h>
#include <drogon/orm/RestfulController.h>

#include "EventsTags.h"
using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::augventure_db;
/**
 * @brief this class is created by the drogon_ctl command.
 * this class is a restful API controller for reading and writing the events_tags table.
 */

class EventsTagsControllerBase : public RestfulController
{
  public:
    void get(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback);
    void create(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback);


//  void update(const HttpRequestPtr &req,
//              std::function<void(const HttpResponsePtr &)> &&callback);

    orm::DbClientPtr getDbClient() 
    {
        return drogon::app().getDbClient(dbClientName_);
    }

  protected:
    /// Ensure that subclasses inherited from this class are instantiated.
    EventsTagsControllerBase();
    const std::string dbClientName_{"default"};
};
