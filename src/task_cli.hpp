#ifndef TASK_CLI_HPP
#define TASK_CLI_HPP

#include <string>
#include "TaskModel.hpp"
#include "TaskStatus.hpp"

namespace task {
    void handle_add_command(int, char* []);
    void handle_update_command(int, char* []);
    void handle_delete_command(int, char* []);
    void handle_mark_as_command(int argc, char* [], task::Status);
    void handle_list_command(int, char* []);
    void handle_help_command();
}

#endif