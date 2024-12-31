#include <string>
#include "TaskService.hpp"
#include "TaskModel.hpp"

task::Service::Service(): repository {} {}
std::tm task::Service::getTmNow() const {
    auto t = std::time(nullptr);
    auto now = *std::localtime(&t);
    std::mktime(&now);
    return now;
}
long task::Service::add(const std::string& description) {
    auto tasks {find("all")};
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
bool task::Service::update(const long& id, const std::string& description) {
    auto tasks {find("all")};
    for(auto& task : tasks) {
        if(task.getId() == id) {
            task.setDescription(description);
            task.setUpdatedAt(getTmNow());
            return repository.saveData(tasks);
        }
    }
    return false;
}
bool task::Service::del(const long& id) {
    auto tasks {find("all")};
    for(auto it {tasks.begin()}; it != tasks.end(); ++it) {
        if(it->getId() == id) {
            tasks.erase(it);
            return repository.saveData(tasks);
        }
    }
    return false;
}
bool task::Service::markAs(const long& id, const task::Status& status) {
    auto tasks {find("all")};
    for(auto& task : tasks) {
        if(task.getId() == id) {
            task.setStatus(status);
            task.setUpdatedAt(getTmNow());
            return repository.saveData(tasks);
        }
    }
    return false;
}
std::vector<task::Model> task::Service::find(const std::string& filter) const {
    return repository.loadData(std::regex {(filter == "all") ? "\"id\":\\d+" : "\"status\":\"" + filter + "\""});
}