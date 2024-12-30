#ifndef TASK_MODEL_HPP
#define TASK_MODEL_HPP

#include <string>
#include <ctime>
#include "TaskStatus.hpp"

namespace task {
    class Model {
        private:
            long id;
            std::string description;
            Status status;
            std::tm createdAt;
            std::tm updatedAt;
            std::string findValue(const std::string&, const std::string&) const;
        public:
            Model();
            Model(const std::string&);
            long getId() const;
            void setId(const long&);
            std::string getDescription() const;
            void setDescription(const std::string&);
            std::string getStatus() const;
            void setStatus(const Status&);
            void setStatus(const std::string&);
            std::string getCreatedAt() const;
            void setCreatedAt(const std::tm&);
            void setCreatedAt(const std::string&);
            std::string getUpdatedAt() const;
            void setUpdatedAt(const std::tm&);
            void setUpdatedAt(const std::string&);
            std::string toJson() const;
            bool equals(const Model&) const;
    };
}

#endif