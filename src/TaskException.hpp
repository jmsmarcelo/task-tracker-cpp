#ifndef TASK_EXCEPTION_HPP
#define TASK_EXCEPTION_HPP

#include <exception>
#include <string>

namespace task {
    class FileWriteException: public std::exception {
        private:
            std::string message;
        public:
            explicit FileWriteException(const std::string&);
            const char* what() const noexcept override;
    };
}

#endif