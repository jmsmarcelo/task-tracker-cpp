#ifndef TASK_REPOSITORY_HPP
#define TASK_REPOSITORY_HPP

#include <string>
#include <vector>
#include <regex>
#include "TaskModel.hpp"

namespace task {
    class Repository {
        private:
            const std::string TASK_DATA_FILE;
            const std::string NEXT_TASK_ID_FILE;
        public:
            Repository();
            bool saveData(const ::std::vector<Model>&);
            std::vector<Model> loadData(const std::regex&) const;
            long loadNextTaskId() const;
            void updateNextTaskId(const long);
    };
}

#endif