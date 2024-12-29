#ifndef TASK_SERVICE_HPP
#define TASK_SERVICE_HPP

#include <ctime>
#include "TaskRepository.hpp"

namespace task {
    class Service {
        private:
            Repository repository;
            std::tm getTmNow() const;
        public:
            Service();
            long add(const std::string&);
    };
}

#endif