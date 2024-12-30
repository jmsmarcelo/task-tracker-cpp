#include <iostream>
#include <string>
#include <regex>
#include <iomanip>
#include "TaskStatus.hpp"
#include "TaskService.hpp"

task::Service service {};

void print_table_line(std::string one, std::string two, std::string three) {
    std::string tableLine {"1────────2────────────────────────────────────────────────────2─────────────2─────────────────────2─────────────────────3"};
    std::regex pattern {R"(1([^\d]+)2([^\d]+)2([^\d]+)2([^\d]+)2([^\d]+)3)"};
    std::smatch match;
    if(std::regex_match(tableLine, match, pattern)) {
        std::cout   << one << match[1].str()
                    << two << match[2].str() << two << match[3].str() << two << match[4].str() << two << match[5].str()
                    << three << '\n';
    }
}
void print_table_content(std::string id, std::string description, std::string status, std::string created_at, std::string updated_at) {
    std::cout   << std::left;
    std::cout   << "│ " << std::setw(6) << id
                << " │ " << std::setw(50) << description
                << " │ " << std::setw(11) << status
                << " │ " << std::setw(19) << created_at
                << " │ " << std::setw(19) << updated_at
                << " │\n";
}
void print_table_content(task::Model task) {
    print_table_content(std::to_string(task.getId()), task.getDescription(), task.getStatus(), task.getCreatedAt(), task.getUpdatedAt());
}
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
    if(argc > 3 || argc == 3 && !task::status_is_valid(argv[2])) {
        std::cout << "invalid command\n"
                  << "  usage:        list [todo|in-progress|done]\n"
                  << "  example:      list\n"
                  << "  example:      list done\n";
        return;
    }
    print_table_line("┌", "┬", "┐");
    print_table_content("  ID", "                   Description", "   Status", "    Created At", "    Updated At");
    std::vector<task::Model> tasks = service.find((argc == 2 ? "all" : argv[2]));
    for(task::Model task : tasks) {
        print_table_line("├", "┼", "┤");
        print_table_content(task);
    }
    print_table_line("└", "┴", "┘");
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