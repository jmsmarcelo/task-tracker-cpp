#include <vector>
#include <fstream>
#include <exception>
#include "TaskRepository.hpp"
#include "TaskModel.hpp"

task::Repository::Repository(): TASK_DATA_FILE {"task-data.json"}, NEXT_TASK_ID_FILE {"next-task-id"} {}
bool task::Repository::saveData(const std::vector<task::Model>& tasks) {
    try {
        std::ofstream taskDataFile {TASK_DATA_FILE};
        taskDataFile << '[';
        for(task::Model task : tasks) {
            taskDataFile    << "\n\t" << task.toJson()
                            << (task.equals(tasks.back()) ? '\n' : ',');
        }
        taskDataFile << ']';
        taskDataFile.close();
        return true;
    } catch(const std::exception& e) {
        return false;
    }
}
long task::Repository::loadNextTaskId() const {
    std::ifstream nextTaskIdFile {NEXT_TASK_ID_FILE};
    long nextTaskId {1};
    if(!nextTaskIdFile.is_open()) {
        return nextTaskId;
    }
    nextTaskIdFile >> nextTaskId;
    nextTaskIdFile.close();
    return nextTaskId;
}
void task::Repository::updateNextTaskId(const long nextTaskId) {
    std::ofstream nextTaskIdFile {NEXT_TASK_ID_FILE};
    nextTaskIdFile << nextTaskId;
    nextTaskIdFile.close();
}