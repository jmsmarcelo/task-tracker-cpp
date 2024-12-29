#ifndef TASK_REPOSITORY_HPP
#define TASK_REPOSITORY_HPP

#include <string>
#include <vector>
#include "TaskModel.hpp"

namespace task {
    class Repository {
        private:
            const std::string TASK_DATA_FILE;
            const std::string NEXT_TASK_ID_FILE;
        public:
            Repository();
            bool saveData(const ::std::vector<Model>&);
            long loadNextTaskId() const;
            void updateNextTaskId(const long);
    };
}

#endif