#include <iostream>
#include <string>
#include <regex>
#include "TaskStatus.hpp"
#include "TaskService.hpp"

task::Service service {};

void handle_add_command(int argc, char* argv[]) {
    if(argc != 3) {
        std::cout   << "invalid command\n"
                    << "    usage:      add <description>\n"
                    << "    example:    add \"Buy groceries\"\n";
        return;
    }
    std::regex pattern {R"(^\s+|\s+$|[\\"]+)"};
    std::string description = std::regex_replace(argv[2], pattern, "");
    if(description.empty()) {
        std::cout << "task description cannot be empty\n";
        return;
    }
    long id {service.add(description)};
    if(id > 0) {
        std::cout << "task added successfully (ID: " << id << ")\n";
    } else {
        std::cout << "failed to add task\n";
    }
}
void handle_update_command(int argc, char* argv[]) {
}
void handle_delete_command(int argc, char* argv[]) {
}
void handle_mark_as_command(int argc, char* argv[], task::Status status) {
}
void handle_list_command(int argc, char* argv[]) {
}
void handle_help_command() {
}

int main(int argc, char* argv[]) {
    if(argc == 1) {
        std::cout << "no command found\n    use 'help' for a list of commands\n";
        return 1;
    }
    std::string command = argv[1];
    if(command == "add") {
        handle_add_command(argc, argv);
    } else if(command == "update") {
        handle_update_command(argc, argv);
    } else if(command == "delete") {
        handle_delete_command(argc, argv);
    } else if(command == "mark-in-progress") {
        handle_mark_as_command(argc, argv, task::Status::IN_PROGRESS);
    } else if(command == "mark-done") {
        handle_mark_as_command(argc, argv, task::Status::DONE);
    } else if(command == "list") {
        handle_list_command(argc, argv);
    } else if(command == "help") {
        handle_help_command();
    } else {
        std::cout << "invalid command\n use 'help' for a list of commands\n";
        return 1;
    }
    return 0;
}