#include "TaskRepository.hpp"

task::Repository::Repository(): db() {
    try {
        db.setSchema(std::getenv("DATABASE_NAME"));
    } catch(sql::SQLException& e) {
        createSchema();
    }
}
void task::Repository::createSchema() {
    try {
        auto* stmt = db.createStatement();
        std::string dbName = std::getenv("DATABASE_NAME");
        stmt->execute("CREATE DATABASE IF NOT EXISTS " + dbName);
        db.setSchema(dbName);
        stmt->execute(
            "CREATE TABLE tasks("
            "   id BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY,"
            "   description VARCHAR(100) NOT NULL,"
            "   status VARCHAR(12) NOT NULL DEFAULT 'todo',"
            "   created_at DATETIME NOT NULL,"
            "   updated_at DATETIME,"
            "   is_deleted BOOLEAN DEFAULT 0"
            ")"
        );
    } catch(sql::SQLException& e) {
        db.cleanup();
        throw;
    }
}
long task::Repository::insert(const std::string& description, const std::string& createdAt) {
    try {
        auto* pstmt = db.prepareStatement(
            "INSERT INTO tasks(description, created_at) VALUES(?, ?)"
        );
        pstmt->setString(1, description);
        pstmt->setString(2, createdAt);
        if(pstmt->executeUpdate() > 0) {
            auto* res = db.executeQuery("SELECT LAST_INSERT_ID()");
            if(res->next()) {
                return res->getInt64(1);
            }
        }
        return 0;
    } catch(sql::SQLException& e) {
        db.cleanup();
        throw;
    }
}
bool task::Repository::updateDescription(const long& id, const std::string& description, const std::string& updatedAt) {
    try {
        auto* pstmt = db.prepareStatement(
            "UPDATE tasks SET description = ?, updated_at = ? WHERE id = ? AND is_deleted = 0"
        );
        pstmt->setString(1, description);
        pstmt->setString(2, updatedAt);
        pstmt->setInt64(3, id);
        return pstmt->executeUpdate() > 0;
    } catch(sql::SQLException& e) {
        db.cleanup();
        throw;
    }
}
bool task::Repository::updateStatus(const long& id, const std::string& status, const std::string& updatedAt) {
    try {
        auto* pstmt = db.prepareStatement(
            "UPDATE tasks SET status = ?, updated_at = ? WHERE id = ? AND is_deleted = 0"
        );
        pstmt->setString(1, status);
        pstmt->setString(2, updatedAt);
        pstmt->setInt64(3, id);
        return pstmt->executeUpdate() > 0;
    } catch(sql::SQLException& e) {
        db.cleanup();
        throw;
    }
}
bool task::Repository::del(const long& id, const std::string& updatedAt) {
    try {
        auto* pstmt = db.prepareStatement(
            "UPDATE tasks SET is_deleted = 1, updated_at = ? WHERE id = ? AND is_deleted = 0"
        );
        pstmt->setString(1, updatedAt);
        pstmt->setInt64(2, id);
        return pstmt->executeUpdate() > 0;
    } catch(sql::SQLException& e) {
        db.cleanup();
        throw;
    }
}
std::vector<task::Model> task::Repository::findAll(bool is_deleted) {
    try {
        auto* pstmt = db.prepareStatement("SELECT * FROM tasks WHERE is_deleted = ?");
        pstmt->setBoolean(1, is_deleted);
        return parseResultSet(pstmt->executeQuery());
    } catch(sql::SQLException& e) {
        db.cleanup();
        throw;
    }
}
std::vector<task::Model> task::Repository::findAllByStatus(const std::string& status, bool is_deleted) {
    try {
        auto* pstmt = db.prepareStatement("SELECT * FROM tasks WHERE status = ? AND is_deleted = ?");
        pstmt->setString(1, status);
        pstmt->setBoolean(2, is_deleted);
        return parseResultSet(pstmt->executeQuery());
    } catch(sql::SQLException& e) {
        db.cleanup();
        throw;
    }
}
std::vector<task::Model> task::Repository::parseResultSet(sql::ResultSet* res) {
    std::vector<task::Model> tasks {};
    while(res->next()) {
        task::Model task {};
        task.setId(res->getInt64("id"));
        task.setDescription(res->getString("description"));
        task.setStatus(res->getString("status"));
        task.setCreatedAt(res->getString("created_at"));
        task.setUpdatedAt(res->getString("updated_at"));
        tasks.push_back(task);
    }
    return tasks;
}