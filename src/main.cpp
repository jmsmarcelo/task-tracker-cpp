#include <locale>
#include <iostream>
#include <string>
#include "task_cli.hpp"

int main(int argc, char* argv[]) {
    std::setlocale(LC_ALL, "en_US.UTF-8");
    if(argc == 1) {
        std::cout << "no command found\n    use 'help' for a list of commands\n";
        return 1;
    }
    std::string command = argv[1];
    if(command == "add") {
        task::handle_add_command(argc, argv);
    } else if(command == "update") {
        task::handle_update_command(argc, argv);
    } else if(command == "delete") {
        task::handle_delete_command(argc, argv);
    } else if(command == "mark-in-progress") {
        task::handle_mark_as_command(argc, argv, task::Status::IN_PROGRESS);
    } else if(command == "mark-done") {
        task::handle_mark_as_command(argc, argv, task::Status::DONE);
    } else if(command == "list") {
        task::handle_list_command(argc, argv);
    } else if(command == "help") {
        task::handle_help_command();
    } else {
        std::cout << "invalid command\n use 'help' for a list of commands\n";
        return 1;
    }
    return 0;
}