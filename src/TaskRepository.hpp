#ifndef TASK_REPOSITORY_HPP
#define TASK_REPOSITORY_HPP

#include <string>
#include <vector>
#include <regex>
#include "Mysql.hpp"
#include "TaskModel.hpp"

namespace task {
    class Repository {
        private:
            MySQL db;
            std::vector<task::Model> parseResultSet(sql::ResultSet*);
        public:
            Repository();
            void createSchema();
            long insert(const std::string&, const std::string&);
            bool updateDescription(const long&, const std::string&, const std::string&);
            bool updateStatus(const long&, const std::string&, const std::string&);
            bool del(const long&, const std::string&);
            std::vector<task::Model> findAll(bool);
            std::vector<task::Model> findAllByStatus(const std::string&, bool);
    };
}

#endif