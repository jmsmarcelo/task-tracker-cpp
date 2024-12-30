#include <vector>
#include <fstream>
#include <exception>
#include <vector>
#include <regex>
#include "TaskRepository.hpp"
#include "TaskModel.hpp"

task::Repository::Repository(): TASK_DATA_FILE {"task-data.json"}, NEXT_TASK_ID_FILE {"next-task-id"} {}
bool task::Repository::saveData(const std::vector<task::Model>& tasks) {
    try {
        std::ofstream taskDataFile {TASK_DATA_FILE};
        taskDataFile << '[';
        for(const auto& task : tasks) {
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
std::vector<task::Model> task::Repository::loadData(const std::regex& pattern) const {
    std::vector<task::Model> tasks;
    std::ifstream taskDataFile {TASK_DATA_FILE};
    std::string json;
    while(std::getline(taskDataFile, json)) {
        if(std::regex_search(json, pattern)) {
            tasks.push_back(task::Model {json});
        }
    }
    taskDataFile.close();
    return tasks;
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