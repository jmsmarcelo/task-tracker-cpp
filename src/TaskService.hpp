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
        public:
            Service();
            long add(const std::string&);
            bool update(const long&, const std::string&);
            bool del(const long&);
            std::vector<Model> find(const std::string&) const;
    };
}

#endif