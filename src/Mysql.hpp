#ifndef MYSQL_HPP
#define MYSQL_HPP

#include <string>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class MySQL {
    private:
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;
    public:
        MySQL();
        ~MySQL();
        void cleanup();
        void setSchema(const std::string&);
        sql::Statement* createStatement();
        sql::PreparedStatement* prepareStatement(const std::string&);
        sql::ResultSet* executeQuery(const std::string&);
        sql::ResultSet* executeQuery();
};

#endif