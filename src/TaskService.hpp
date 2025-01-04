#ifndef TASK_SERVICE_HPP
#define TASK_SERVICE_HPP

#include <ctime>
#include <vector>
#include "TaskRepository.hpp"

namespace task {
    class Service {
        private:
            Repository repository;
            std::tm getTmNow() const;
            std::string getStringNow();
        public:
            Service();
            long add(const std::string&);
            bool update(const long&, const std::string&);
            bool del(const long&);
            bool markAs(const long&, const task::Status&);
            std::vector<Model> find(const std::string&);
    };
}

#endif