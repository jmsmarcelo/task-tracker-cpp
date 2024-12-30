#include <iostream>
#include <string>
#include <regex>
#include <iomanip>
#include "TaskStatus.hpp"
#include "TaskService.hpp"

task::Service service {};

void print_table_line(const std::string& one, const std::string& two, const std::string& three) {
    std::string tableLine {"1────────2────────────────────────────────────────────────────2─────────────2─────────────────────2─────────────────────3"};
    std::regex pattern {R"(1([^\d]+)2([^\d]+)2([^\d]+)2([^\d]+)2([^\d]+)3)"};
    std::smatch match;
    if(std::regex_match(tableLine, match, pattern)) {
        std::cout   << one << match[1].str()
                    << two << match[2].str() << two << match[3].str() << two << match[4].str() << two << match[5].str()
                    << three << '\n';
    }
}
void print_table_content(
    const std::string& id, const std::string& description, const std::string& status,
    const std::string& created_at, const std::string& updated_at) {
        std::cout   << std::left;
        std::cout   << "│ " << std::setw(6) << id
                    << " │ " << std::setw(50) << description
                    << " │ " << std::setw(11) << status
                    << " │ " << std::setw(19) << created_at
                    << " │ " << std::setw(19) << updated_at
                    << " │\n";
}
void print_table_content(const task::Model& task) {
    print_table_content(std::to_string(task.getId()), task.getDescription(), task.getStatus(), task.getCreatedAt(), task.getUpdatedAt());
}
void handle_add_command(int argc, char* argv[]) {
    if(argc != 3) {
        std::cout   << "invalid command\n"
                    << "    usage:      add <description>\n"
                    << "    example:    add \"Buy groceries\"\n";
        return;
    }
    std::string description = std::regex_replace(argv[2], std::regex {R"(^\s+|\s+$|[\\"]+)"}, "");
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
    if(argc != 4 || !std::regex_match(argv[2], std::regex {"\\d+"})) {
        std::cout   << "invalid command\n"
                    << "    usage:      update <id> <description\n"
                    << "    example:    update 1 \"Buy groceries and cook dinner\"\n";
        return; 
    }
    auto id = std::stol(argv[2]);
    std::string description {std::regex_replace(argv[3], std::regex {R"(^\s+|\s+$|[\\"]+)"}, "")};
    if(description.empty()) {
        std::cout << "task description cannot be empty\n";
        return;
    }
    if(service.update(id, description)) {
        std::cout << "task updated successfully\n";
    } else {
        std::cout   << "failed to update task\n"
                    << "    task id not found\n";
    }
}
void handle_delete_command(int argc, char* argv[]) {
    if(argc != 3 || !std::regex_match(argv[2], std::regex(R"(\d+)"))) {
        std::cout << "invalid command\n"
                  << "  usage:        delete <id>\n"
                  << "  example:      delete 1\n";
        return;
    }
    if(service.del(std::stol(argv[2]))) {
        std::cout << "task deleted successfully\n";
    } else {
        std::cout   << "failed to delete task\n"
                    << "  task id not found\n";
    }
}
void handle_mark_as_command(int argc, char* argv[], task::Status status) {
    if(argc != 3 || !std::regex_match(argv[2], std::regex(R"(\d+)")) || !task::status_is_valid(task::status_to_string(status))) {
        std::cout << "invalid command\n"
                  << "  usage:        " << argv[1] << " <id>\n"
                  << "  example:      " << argv[1] << " 1\n";
        return;
    }
    if(service.markAs(std::stol(argv[2]), status)) {
        std::cout << "task marked as " << task::status_to_string(status) << " successfully\n";
    } else {
        std::cout   << "failed to mark task as " << task::status_to_string(status) << "\n"
                    << "  task id not found\n";
    }
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
    auto tasks {service.find((argc == 2 ? "all" : argv[2]))};
    for(const auto& task : tasks) {
        print_table_line("├", "┼", "┤");
        print_table_content(task);
    }
    print_table_line("└", "┴", "┘");
}
void handle_help_command() {
    std::cout << "----------------------------- Task Tracker CLI - Help -----------------------------\n";
    std::cout << "Available commands:\n";
    std::cout << "  add <description>           - add a new task with the given description\n";
    std::cout << "  update <id> <description>   - Update the task with the given ID\n";
    std::cout << "  delete <id>                 - Delete the task with the given ID\n";
    std::cout << "  mark-in-progress <id>       - Mark the task with the given ID as in-progress\n";
    std::cout << "  mark-done <id>              - Mark the task with the given ID as done\n";
    std::cout << "  list                        - List all tasks\n";
    std::cout << "  list todo                   - List all tasks with status 'todo'\n";
    std::cout << "  list in-progress            - List all tasks with status 'in-progress'\n";
    std::cout << "  list done                   - List all tasks with status 'done'\n";
    std::cout << "  help                        - Display this help message\n\n";
    std::cout << "Example usage:\n";
    std::cout << "  add \"Buy groceries\"\n";
    std::cout << "  update 1 \"Buy groceries and cook dinner\"\n";
    std::cout << "  delete 1\n";
    std::cout << "  mark-in-progress 1\n";
    std::cout << "  mark-done 1\n";
    std::cout << "  list\n";
    std::cout << "  list done\n";
    std::cout << "-----------------------------------------------------------------------------------\n";
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