#include <ctime>
#include <vector>
#include <string>
#include "TaskService.hpp"
#include "TaskRepository.hpp"
#include "TaskModel.hpp"

task::Service::Service(): repository {} {}
std::tm task::Service::getTmNow() const {
    std::time_t t = std::time(nullptr);
    std::tm now = *std::localtime(&t);
    std::mktime(&now);
    return now;
}
long task::Service::add(const std::string& description) {
    std::vector<task::Model> tasks {};
    task::Model task;
    task.setId(repository.loadNextTaskId());
    task.setDescription(description);
    task.setCreatedAt(getTmNow());
    tasks.push_back(task);
    if(repository.saveData(tasks)) {
        repository.updateNextTaskId(task.getId() + 1);
        return task.getId();
    }
    return 0;
}