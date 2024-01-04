/**
 *
 *  Suggestions.h
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#pragma once
#include <drogon/orm/BaseBuilder.h>
#include <drogon/orm/Field.h>
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>
#include <drogon/orm/SqlBinder.h>
#ifdef __cpp_impl_coroutine
#include <drogon/orm/CoroMapper.h>
#endif
#include <iostream>
#include <json/json.h>
#include <memory>
#include <stdint.h>
#include <string>
#include <string_view>
#include <trantor/utils/Date.h>
#include <trantor/utils/Logger.h>
#include <tuple>
#include <vector>

namespace drogon
{
namespace orm
{
class DbClient;
using DbClientPtr = std::shared_ptr<DbClient>;
} // namespace orm
} // namespace drogon
namespace drogon_model
{
namespace augventure_db
{
class Posts;
class Sprints;

class Suggestions
{
public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _author_id;
        static const std::string _post_date;
        static const std::string _sprint_id;
        static const std::string _votes;
    };

    const static int primaryKeyNumber;
    const static std::string tableName;
    const static bool hasPrimaryKey;
    const static std::string primaryKeyName;
    using PrimaryKeyType = uint32_t;
    const PrimaryKeyType& getPrimaryKey() const;

    /**
     * @brief constructor
     * @param r One row of records in the SQL query result.
     * @param indexOffset Set the offset to -1 to access all columns by column
     * names, otherwise access all columns by offsets.
     * @note If the SQL is not a style of 'select * from table_name ...' (select
     * all columns by an asterisk), please set the offset to -1.
     */
    explicit Suggestions(const drogon::orm::Row& r,
                         const ssize_t indexOffset = 0) noexcept;

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     */
    explicit Suggestions(const Json::Value& pJson) noexcept(false);

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     * @param pMasqueradingVector The aliases of table columns.
     */
    Suggestions(
        const Json::Value& pJson,
        const std::vector<std::string>& pMasqueradingVector) noexcept(false);

    Suggestions() = default;

    void updateByJson(const Json::Value& pJson) noexcept(false);
    void updateByMasqueradedJson(
        const Json::Value& pJson,
        const std::vector<std::string>& pMasqueradingVector) noexcept(false);
    static bool validateJsonForCreation(const Json::Value& pJson,
                                        std::string& err);
    static bool validateMasqueradedJsonForCreation(
        const Json::Value&, const std::vector<std::string>& pMasqueradingVector,
        std::string& err);
    static bool validateJsonForUpdate(const Json::Value& pJson,
                                      std::string& err);
    static bool validateMasqueradedJsonForUpdate(
        const Json::Value&, const std::vector<std::string>& pMasqueradingVector,
        std::string& err);
    static bool validJsonOfField(size_t index, const std::string& fieldName,
                                 const Json::Value& pJson, std::string& err,
                                 bool isForCreation);

    /**  For column id  */
    /// Get the value of the column id, returns the default value if the column
    /// is null
    const uint32_t& getValueOfId() const noexcept;
    /// Return a shared_ptr object pointing to the column const value, or an
    /// empty shared_ptr object if the column is null
    const std::shared_ptr<uint32_t>& getId() const noexcept;
    /// Set the value of the column id
    void setId(const uint32_t& pId) noexcept;

    /**  For column author_id  */
    /// Get the value of the column author_id, returns the default value if the
    /// column is null
    const uint32_t& getValueOfAuthorId() const noexcept;
    /// Return a shared_ptr object pointing to the column const value, or an
    /// empty shared_ptr object if the column is null
    const std::shared_ptr<uint32_t>& getAuthorId() const noexcept;
    /// Set the value of the column author_id
    void setAuthorId(const uint32_t& pAuthorId) noexcept;

    /**  For column post_date  */
    /// Get the value of the column post_date, returns the default value if the
    /// column is null
    const ::trantor::Date& getValueOfPostDate() const noexcept;
    /// Return a shared_ptr object pointing to the column const value, or an
    /// empty shared_ptr object if the column is null
    const std::shared_ptr<::trantor::Date>& getPostDate() const noexcept;
    /// Set the value of the column post_date
    void setPostDate(const ::trantor::Date& pPostDate) noexcept;

    /**  For column sprint_id  */
    /// Get the value of the column sprint_id, returns the default value if the
    /// column is null
    const uint32_t& getValueOfSprintId() const noexcept;
    /// Return a shared_ptr object pointing to the column const value, or an
    /// empty shared_ptr object if the column is null
    const std::shared_ptr<uint32_t>& getSprintId() const noexcept;
    /// Set the value of the column sprint_id
    void setSprintId(const uint32_t& pSprintId) noexcept;

    /**  For column votes  */
    /// Get the value of the column votes, returns the default value if the
    /// column is null
    const int32_t& getValueOfVotes() const noexcept;
    /// Return a shared_ptr object pointing to the column const value, or an
    /// empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t>& getVotes() const noexcept;
    /// Set the value of the column votes
    void setVotes(const int32_t& pVotes) noexcept;

    static size_t getColumnNumber() noexcept { return 5; }
    static const std::string& getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;
    Json::Value toMasqueradedJson(
        const std::vector<std::string>& pMasqueradingVector) const;
    /// Relationship interfaces
    Posts getPost(const drogon::orm::DbClientPtr& clientPtr) const;
    void getPost(const drogon::orm::DbClientPtr& clientPtr,
                 const std::function<void(Posts)>& rcb,
                 const drogon::orm::ExceptionCallback& ecb) const;
    Sprints getSprint(const drogon::orm::DbClientPtr& clientPtr) const;
    void getSprint(const drogon::orm::DbClientPtr& clientPtr,
                   const std::function<void(Sprints)>& rcb,
                   const drogon::orm::ExceptionCallback& ecb) const;

private:
    friend drogon::orm::Mapper<Suggestions>;
    friend drogon::orm::BaseBuilder<Suggestions, true, true>;
    friend drogon::orm::BaseBuilder<Suggestions, true, false>;
    friend drogon::orm::BaseBuilder<Suggestions, false, true>;
    friend drogon::orm::BaseBuilder<Suggestions, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<Suggestions>;
#endif
    static const std::vector<std::string>& insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder& binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder& binder) const;
    /// For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<uint32_t> id_;
    std::shared_ptr<uint32_t> authorId_;
    std::shared_ptr<::trantor::Date> postDate_;
    std::shared_ptr<uint32_t> sprintId_;
    std::shared_ptr<int32_t> votes_;
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
    bool dirtyFlag_[5] = { false };

public:
    static const std::string& sqlForFindingByPrimaryKey()
    {
        static const std::string sql =
            "select * from " + tableName + " where id = ?";
        return sql;
    }

    static const std::string& sqlForDeletingByPrimaryKey()
    {
        static const std::string sql =
            "delete from " + tableName + " where id = ?";
        return sql;
    }
    std::string sqlForInserting(bool& needSelection) const
    {
        std::string sql = "insert into " + tableName + " (";
        size_t parametersCount = 0;
        needSelection = false;
        sql += "id,";
        ++parametersCount;
        if (dirtyFlag_[1])
        {
            sql += "author_id,";
            ++parametersCount;
        }
        sql += "post_date,";
        ++parametersCount;
        if (!dirtyFlag_[2])
        {
            needSelection = true;
        }
        if (dirtyFlag_[3])
        {
            sql += "sprint_id,";
            ++parametersCount;
        }
        sql += "votes,";
        ++parametersCount;
        if (!dirtyFlag_[4])
        {
            needSelection = true;
        }
        needSelection = true;
        if (parametersCount > 0)
        {
            sql[sql.length() - 1] = ')';
            sql += " values (";
        }
        else
            sql += ") values (";

        sql += "default,";
        if (dirtyFlag_[1])
        {
            sql.append("?,");
        }
        if (dirtyFlag_[2])
        {
            sql.append("?,");
        }
        else
        {
            sql += "default,";
        }
        if (dirtyFlag_[3])
        {
            sql.append("?,");
        }
        if (dirtyFlag_[4])
        {
            sql.append("?,");
        }
        else
        {
            sql += "default,";
        }
        if (parametersCount > 0)
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
