#include <string>
#include <sstream>
#include <iomanip>
#include "TaskService.hpp"
#include "TaskModel.hpp"

task::Service::Service(): repository {} {}
std::tm task::Service::getTmNow() const {
    auto t = std::time(nullptr);
    auto now = *std::localtime(&t);
    std::mktime(&now);
    return now;
}
std::string task::Service::getStringNow() {
    std::ostringstream oss;
    std::tm now = getTmNow();
    oss << std::put_time(&now, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
long task::Service::add(const std::string& description) {
    return repository.insert(description, getStringNow());
}
bool task::Service::update(const long& id, const std::string& description) {
    return repository.updateDescription(id, description, getStringNow());
}
bool task::Service::del(const long& id) {
    return repository.del(id, getStringNow());
}
bool task::Service::markAs(const long& id, const task::Status& status) {
    return repository.updateStatus(id, task::status_to_string(status), getStringNow());
}
std::vector<task::Model> task::Service::find(const std::string& filter) {
    if(filter == "all") {
        return repository.findAll(0);
    }
    return repository.findAllByStatus(filter, 0);
}