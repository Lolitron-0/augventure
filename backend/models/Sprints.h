/**
 *
 *  Sprints.h
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#pragma once
#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>
#include <drogon/orm/Field.h>
#include <drogon/orm/SqlBinder.h>
#include <drogon/orm/Mapper.h>
#include <drogon/orm/BaseBuilder.h>
#ifdef __cpp_impl_coroutine
#include <drogon/orm/CoroMapper.h>
#endif
#include <trantor/utils/Date.h>
#include <trantor/utils/Logger.h>
#include <json/json.h>
#include <string>
#include <string_view>
#include <memory>
#include <vector>
#include <tuple>
#include <stdint.h>
#include <iostream>

namespace drogon
{
namespace orm
{
class DbClient;
using DbClientPtr = std::shared_ptr<DbClient>;
}
}
namespace drogon_model
{
namespace augventure_db
{

class Sprints
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _state;
        static const std::string _suggestion_winner_id;
        static const std::string _event_id;
        static const std::string _start;
    };

    const static int primaryKeyNumber;
    const static std::string tableName;
    const static bool hasPrimaryKey;
    const static std::string primaryKeyName;
    using PrimaryKeyType = uint32_t;
    const PrimaryKeyType &getPrimaryKey() const;

    /**
     * @brief constructor
     * @param r One row of records in the SQL query result.
     * @param indexOffset Set the offset to -1 to access all columns by column names,
     * otherwise access all columns by offsets.
     * @note If the SQL is not a style of 'select * from table_name ...' (select all
     * columns by an asterisk), please set the offset to -1.
     */
    explicit Sprints(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     */
    explicit Sprints(const Json::Value &pJson) noexcept(false);

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     * @param pMasqueradingVector The aliases of table columns.
     */
    Sprints(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);

    Sprints() = default;

    void updateByJson(const Json::Value &pJson) noexcept(false);
    void updateByMasqueradedJson(const Json::Value &pJson,
                                 const std::vector<std::string> &pMasqueradingVector) noexcept(false);
    static bool validateJsonForCreation(const Json::Value &pJson, std::string &err);
    static bool validateMasqueradedJsonForCreation(const Json::Value &,
                                                const std::vector<std::string> &pMasqueradingVector,
                                                    std::string &err);
    static bool validateJsonForUpdate(const Json::Value &pJson, std::string &err);
    static bool validateMasqueradedJsonForUpdate(const Json::Value &,
                                          const std::vector<std::string> &pMasqueradingVector,
                                          std::string &err);
    static bool validJsonOfField(size_t index,
                          const std::string &fieldName,
                          const Json::Value &pJson,
                          std::string &err,
                          bool isForCreation);

    /**  For column id  */
    ///Get the value of the column id, returns the default value if the column is null
    const uint32_t &getValueOfId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<uint32_t> &getId() const noexcept;
    ///Set the value of the column id
    void setId(const uint32_t &pId) noexcept;

    /**  For column state  */
    ///Get the value of the column state, returns the default value if the column is null
    const std::string &getValueOfState() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getState() const noexcept;
    ///Set the value of the column state
    void setState(const std::string &pState) noexcept;
    void setState(std::string &&pState) noexcept;
    void setStateToNull() noexcept;

    /**  For column suggestion_winner_id  */
    ///Get the value of the column suggestion_winner_id, returns the default value if the column is null
    const uint32_t &getValueOfSuggestionWinnerId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<uint32_t> &getSuggestionWinnerId() const noexcept;
    ///Set the value of the column suggestion_winner_id
    void setSuggestionWinnerId(const uint32_t &pSuggestionWinnerId) noexcept;
    void setSuggestionWinnerIdToNull() noexcept;

    /**  For column event_id  */
    ///Get the value of the column event_id, returns the default value if the column is null
    const uint32_t &getValueOfEventId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<uint32_t> &getEventId() const noexcept;
    ///Set the value of the column event_id
    void setEventId(const uint32_t &pEventId) noexcept;

    /**  For column start  */
    ///Get the value of the column start, returns the default value if the column is null
    const ::trantor::Date &getValueOfStart() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<::trantor::Date> &getStart() const noexcept;
    ///Set the value of the column start
    void setStart(const ::trantor::Date &pStart) noexcept;
    void setStartToNull() noexcept;


    static size_t getColumnNumber() noexcept {  return 5;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;
    Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;
    /// Relationship interfaces
  private:
    friend drogon::orm::Mapper<Sprints>;
    friend drogon::orm::BaseBuilder<Sprints, true, true>;
    friend drogon::orm::BaseBuilder<Sprints, true, false>;
    friend drogon::orm::BaseBuilder<Sprints, false, true>;
    friend drogon::orm::BaseBuilder<Sprints, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<Sprints>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<uint32_t> id_;
    std::shared_ptr<std::string> state_;
    std::shared_ptr<uint32_t> suggestionWinnerId_;
    std::shared_ptr<uint32_t> eventId_;
    std::shared_ptr<::trantor::Date> start_;
    struct MetaData
    {
        const std::string colName_;
        const std::string colType_;
        const std::string colDatabaseType_;
        const ssize_t colLength_;
        const bool isAutoVal_;
        const bool isPrimaryKey_;
        const bool notNull_;
    };
    static const std::vector<MetaData> metaData_;
    bool dirtyFlag_[5]={ false };
  public:
    static const std::string &sqlForFindingByPrimaryKey()
    {
        static const std::string sql="select * from " + tableName + " where id = ?";
        return sql;
    }

    static const std::string &sqlForDeletingByPrimaryKey()
    {
        static const std::string sql="delete from " + tableName + " where id = ?";
        return sql;
    }
    std::string sqlForInserting(bool &needSelection) const
    {
        std::string sql="insert into " + tableName + " (";
        size_t parametersCount = 0;
        needSelection = false;
            sql += "id,";
            ++parametersCount;
        if(dirtyFlag_[1])
        {
            sql += "state,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "suggestion_winner_id,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "event_id,";
            ++parametersCount;
        }
        sql += "start,";
        ++parametersCount;
        if(!dirtyFlag_[4])
        {
            needSelection=true;
        }
        needSelection=true;
        if(parametersCount > 0)
        {
            sql[sql.length()-1]=')';
            sql += " values (";
        }
        else
            sql += ") values (";

        sql +="default,";
        if(dirtyFlag_[1])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[2])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[3])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[4])
        {
            sql.append("?,");

        }
        else
        {
            sql +="default,";
        }
        if(parametersCount > 0)
        {
            sql.resize(sql.length() - 1);
        }
        sql.append(1, ')');
        LOG_TRACE << sql;
        return sql;
    }
};
} // namespace augventure_db
} // namespace drogon_model
