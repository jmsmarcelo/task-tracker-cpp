#include <string>
#include <iostream>
#include "TaskStatus.hpp"

std::string task::status_to_string(const task::Status& status) {
    switch(status) {
        case task::Status::TODO:
            return "todo";
        case task::Status::IN_PROGRESS:
            return "in-progress";
        case task::Status::DONE:
            return "done";
        default:
            return "";
    }
}
task::Status task::status_from_string(const std::string& status) {
    if(status == "todo") {
        return task::Status::TODO;
    } else if(status == "in-progress") {
        return task::Status::IN_PROGRESS;
    } else if(status == "done") {
        return task::Status::DONE;
    }
    throw std::invalid_argument("invalid task status");
}