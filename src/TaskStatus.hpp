#ifndef TASK_STATUS_HPP
#define TASK_STATUS_HPP

#include <string>

namespace task {
    enum class Status {
        TODO, IN_PROGRESS, DONE
    };
    std::string status_to_string(const Status&);
    Status status_from_string(const std::string&);
    bool status_is_valid(const std::string&);
}

#endif