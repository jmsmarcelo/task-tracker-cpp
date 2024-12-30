#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <map>
#include <regex>
#include "TaskModel.hpp"
#include "TaskStatus.hpp"

task::Model::Model(): id {0}, description {""}, status {task::Status::TODO}, createdAt {}, updatedAt {} {}
task::Model::Model(const std::string& json): Model() {
    std::map<std::string, std::string> data;
    data["id"] = findValue(R"("id":(\d+),)", json);
    data["description"] = findValue(R"::("description":"([^"]+)",)::", json);
    data["status"] = findValue(R"::("status":"([^"]+)",)::", json);
    data["createdAt"] = findValue(R"::("created_at":"(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})",)::", json);
    data["updatedAt"] = findValue(R"::("updated_at":"(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})")::", json);
    if(data["id"] != "") {
        setId(std::stol(data["id"]));
    }
    if(data["description"] != "") {
        setDescription(data["description"]);
    }
    if(data["status"] != "") {
        setStatus(data["status"]);
    }
    if(data["createdAt"] != "") {
        setCreatedAt(data["createdAt"]);
    }
    if(data["updatedAt"] != "") {
        setUpdatedAt(data["updatedAt"]);
    }
}
long task::Model::getId() const {
    return id;
}
void task::Model::setId(const long& id) {
    this->id = id;
}
std::string task::Model::getDescription() const {
    return description;
}
void task::Model::setDescription(const std::string& description) {
    this->description = description;
}
std::string task::Model::getStatus() const {
    return task::status_to_string(status);
}
void task::Model::setStatus(const task::Status& status) {
    this->status = status;
}
void task::Model::setStatus(const std::string& status) {
    this->status = task::status_from_string(status);
}
std::string task::Model::getCreatedAt() const {
    if(createdAt.tm_year == 0) {
        return "null";
    }
    std::ostringstream oss;
    oss << std::put_time(&createdAt, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
void task::Model::setCreatedAt(const std::tm& createdAt) {
    this->createdAt = createdAt;
}
void task::Model::setCreatedAt(const std::string& createdAt) {
    std::istringstream iss {createdAt};
    iss >> std::get_time(&this->createdAt, "%Y-%m-%d %H:%M:%S");
}
std::string task::Model::getUpdatedAt() const {
    if(updatedAt.tm_year == 0) {
        return "null";
    }
    std::ostringstream oss;
    oss << std::put_time(&updatedAt, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
void task::Model::setUpdatedAt(const std::tm& updatedAt) {
    this->updatedAt = updatedAt;
}
void task::Model::setUpdatedAt(const std::string& updatedAt) {
    std::istringstream iss {updatedAt};
    iss >> std::get_time(&this->updatedAt, "%Y-%m-%d %H:%M:%S");
}
std::string task::Model::toJson() const {
    std::ostringstream oss;
    oss << '{'
        << "\"id\":" << getId() << ','
        << "\"description\":\"" << getDescription() << "\","
        << "\"status\":\"" << getStatus() << "\","
        << "\"created_at\":\"" << getCreatedAt() << "\","
        << "\"updated_at\":\"" << getUpdatedAt() << '"'
        << '}';
    return oss.str();
}
bool task::Model::equals(const task::Model& other) const {
    return getId() == other.getId()
        && getDescription() == other.getDescription()
        && getStatus() == other.getStatus()
        && getCreatedAt() == other.getCreatedAt()
        && getUpdatedAt() == other.getUpdatedAt();
}

std::string task::Model::findValue(const std::string& pattern, const std::string& json) const {
    std::smatch match;
    if(std::regex_search(json, match, std::regex {pattern})) {
        return match.str(1);
    }
    return "";
}