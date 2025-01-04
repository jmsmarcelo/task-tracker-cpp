#include "Mysql.hpp"

MySQL::MySQL(): driver(get_driver_instance()), stmt(nullptr), pstmt(nullptr), res(nullptr) {
    try {
        con = driver->connect(std::getenv("DATABASE_URL"), std::getenv("DATABASE_USER"), std::getenv("DATABASE_PASS"));
    } catch(sql::SQLException& e) {
        cleanup();
        throw;
    }
}
MySQL::~MySQL() {
    cleanup();
}
void MySQL::cleanup() {
    delete con;
    delete stmt;
    delete pstmt;
    delete res;
}
void MySQL::setSchema(const std::string& dbName) {
    con->setSchema(dbName);
}
sql::Statement* MySQL::createStatement() {
    if(stmt) delete stmt;
    return stmt = con->createStatement();
}
sql::PreparedStatement* MySQL::prepareStatement(const std::string& sql) {
    if(pstmt) delete pstmt;
    return pstmt = con->prepareStatement(sql);
}
sql::ResultSet* MySQL::executeQuery(const std::string& sql) {
    createStatement();
    if(res) delete res;
    return res = stmt->executeQuery(sql);
}
sql::ResultSet* MySQL::executeQuery() {
    if(res) delete res;
    return res = pstmt->executeQuery();
}