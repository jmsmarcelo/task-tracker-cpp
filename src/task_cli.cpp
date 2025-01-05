#include <iostream>
#include <regex>
#include <iomanip>
#include <map>
#include "task_cli.hpp"
#include "TaskService.hpp"
#include "TaskException.hpp"

task::Service service {};
size_t get_width(const std::string& txt) {
    size_t count = 0;
    for(unsigned char c : txt) {
        if((c & 0xC0) != 0x80) {
            ++count;
        }
    }
    return count;
}
std::string text_format(const std::string& txt, size_t width, const char32_t complement, char position) {
    size_t w = get_width(txt);
    if(width <= w) return txt;

    size_t total_space = width - w;
    size_t left_space = 0;
    size_t right_space = total_space;
    if(position == 'c') {
        left_space = total_space / 2;
        right_space = total_space - left_space;
    } else if(position == 'r') {
        left_space = total_space;
        right_space = 0;
    }
    return std::string(left_space, complement) + txt + std::string(right_space, complement);
}
void print_table_line(const  std::map<std::string, size_t>& widths) {
    std::cout   << "+-" << text_format("", widths.at("id"), '-', 'l')
                << "-+-" << text_format("", widths.at("description"), '-', 'l')
                << "-+-" << text_format("", widths.at("status"), '-', 'l')
                << "-+-" << text_format("", widths.at("created_at"), '-', 'l')
                << "-+-" << text_format("", widths.at("updated_at"), '-', 'l')
                << "-+" << '\n';
}
void print_table_content(
    const std::string& id, const std::string& description, const std::string& status,
    const std::string& created_at, const std::string& updated_at,  const  std::map<std::string, size_t>& widths, const char32_t complement, char position = 'l') {
        std::cout   << "│ " << text_format(id, widths.at("id"), complement, position)
                    << " │ " << text_format(description, widths.at("description"), complement, position)
                    << " │ " << text_format(status, widths.at("status"), complement, position)
                    << " │ " << text_format(created_at, widths.at("created_at"), complement, position)
                    << " │ " << text_format(updated_at, widths.at("updated_at"), complement, position)
                    << " │\n";
}
void print_table(const std::vector<task::Model>& tasks) {
    std::map<std::string, size_t> widths{{"id", 6}, {"description", 11}, {"status", 11}, {"created_at", 19}, {"updated_at", 19}};
    for(const auto& task : tasks) {
        if(get_width(task.getDescription()) > widths.at("description")) {
            widths.at("description") = get_width(task.getDescription());
        }
    }
    print_table_line(widths);
    print_table_content("ID", "Description", "Status", "Created At", "Updated At", widths, ' ', 'c');
    for(const auto& task : tasks) {
        print_table_line(widths);
        print_table_content(std::to_string(task.getId()), task.getDescription(), task.getStatus(), task.getCreatedAt(), task.getUpdatedAt(), widths, ' ');
    }
    print_table_line(widths);
}
void task::handle_add_command(int argc, char* argv[]) {
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
    try {
        long id {service.add(description)};
        if(id > 0) {
            std::cout << "task added successfully (ID: " << id << ")\n";
        } else {
            std::cout << "failed to add task\n";
        }
    } catch(task::FileWriteException& e) {
        std::cout   << "failed to add task\n   "
                    << e.what() << '\n';
    }
}
void task::handle_update_command(int argc, char* argv[]) {
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
    try {
        if(service.update(id, description)) {
            std::cout << "task updated successfully\n";
        } else {
            std::cout   << "failed to update task\n"
                        << "    task id not found\n";
        }
    } catch(task::FileWriteException& e) {
        std::cout   << "failed to update task\n   "
                    << e.what() << '\n';
    }
}
void task::handle_delete_command(int argc, char* argv[]) {
    if(argc != 3 || !std::regex_match(argv[2], std::regex(R"(\d+)"))) {
        std::cout << "invalid command\n"
                  << "  usage:        delete <id>\n"
                  << "  example:      delete 1\n";
        return;
    }
    try {
        if(service.del(std::stol(argv[2]))) {
            std::cout << "task deleted successfully\n";
        } else {
            std::cout   << "failed to delete task\n"
                        << "  task id not found\n";
        }
    } catch(task::FileWriteException& e) {
        std::cout   << "failed to delete task\n   "
                    << e.what() << '\n';
    }
}
void task::handle_mark_as_command(int argc, char* argv[], task::Status status) {
    if(argc != 3 || !std::regex_match(argv[2], std::regex(R"(\d+)"))) {
        std::cout << "invalid command\n"
                  << "  usage:        " << argv[1] << " <id>\n"
                  << "  example:      " << argv[1] << " 1\n";
        return;
    }
    try {
        if(service.markAs(std::stol(argv[2]), status)) {
            std::cout << "task marked as " << task::status_to_string(status) << " successfully\n";
        } else {
            std::cout   << "failed to mark task as " << task::status_to_string(status) << "\n"
                        << "  task id not found\n";
        }
    } catch(task::FileWriteException& e) {
        std::cout   << "failed to mark task as " << task::status_to_string(status) << "\n   "
                    << e.what() << '\n';
    }
}
void task::handle_list_command(int argc, char* argv[]) {
    if(argc > 3 || argc == 3 && !task::status_is_valid(argv[2])) {
        std::cout << "invalid command\n"
                  << "  usage:        list [todo|in-progress|done]\n"
                  << "  example:      list\n"
                  << "  example:      list done\n";
        return;
    }
    print_table(service.find((argc == 2 ? "all" : argv[2])));
}
void task::handle_help_command() {
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