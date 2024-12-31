# Task Tracker CLI

A command-line application for tracking and managing tasks, developed in **C++** as part of the [Task Tracker Project](https://roadmap.sh/projects/task-tracker) by **Roadmap.sh**.

## 📋 Features
- Add, Update, and Delete tasks
- Mark a task as in progress or done
- List all tasks
- List all tasks are not done
- List all tasks are in progress
- List all tasks are done

## ⚙️ Technologies and Tools

- Language: **C++**
- CLI Structure: Input/output handling
- Data Persistence: Store the tasks in a JSON file

## 🛠️ How to Run the Project

### Prerequisites

- For compile:
  - **Windows**: MSVC (Visual Studio Developer Command Prompt)
  - **Linux**: GCC (GNU Compiler Collection)
- For execute:
  - Read/write permission

### Steps to Execute

1. Clone the repository:
   ```bash
   git clone https://github.com/jmsmarcelo/task-tracker-cli-cpp.git
   cd task-tracker-cli-cpp
   ```
2. Compile the project:
   ```bash
   mkdir bin
   cd bin

   # Linux:
   g++ -o task-cli ../src/*.cpp

   # Windows (Visual Studio Developer Command Prompt):
   cl /EHsc /Fe:task-cli.exe ..\src\*.cpp
   ```
3. Run the application:
   ```bash
   # Linux:
   ./task-cli help

   # Windows:
   .\task-cli help
   ```

## 📌 Usage
```bash
# Adding a new task
task-cli add "Buy groceries"
# output: Task added successfully (ID: 1)

# Updating task
task-cli update 1 "Buy groceries and cook dinner"
# output: Task updated successfully

# Deleting task
task-cli delete 1
# output: Task deleted successfully

# Marking a task as in progress
task-cli mark-in-progress 1
# output: Task marked as in-progress successfully

# Marking a task as done
task-cli mark-done 1
# output: Task marked as done successfully

# Listing all tasks
task-cli list
# output: ┌────────┬────────────────────────────────────────────────────┬─────────────┬─────────────────────┬─────────────────────┐
#         │   ID   │                    Description                     │    Status   │     Created At      │     Updated At      │
#         ├────────┼────────────────────────────────────────────────────┼─────────────┼─────────────────────┼─────────────────────┤
#         │ 1      │ Buy groceries and cook dinner                      │ todo        │ 2024-12-31 09:14:19 │ 2024-12-31 09:24:32 │
#         └────────┴────────────────────────────────────────────────────┴─────────────┴─────────────────────┴─────────────────────┘

# Listing tasks by status
task-cli list todo
task-cli list in-progress
task-cli list done
```

## 📦 Project Structure
```bash
task-tracker-cli-cpp/
└─ src/
   ├─ task_cli.cpp         # Application entry point
   ├─ TaskModel.hpp        # Task domain model declaration header
   ├─ TaskModel.cpp        # Task domain model definition file
   ├─ TaskStatus.hpp       # Task status enum declaration header
   ├─ TaskStatus.cpp       # Task status enum definition file
   ├─ TaskService.hpp      # Task service logic declaration header
   ├─ TaskService.cpp      # Task service logic definition file
   ├─ TaskRepository.hpp   # File persistence handling declaration header
   └─ TaskRepository.cpp   # File persistence handling definition file
```
## 🖼️ Screenshots
![Screenshot 2024-12-31 181609](https://github.com/user-attachments/assets/f274169f-12d0-47f7-aec7-b496013f8205)
![Screenshot 2024-12-31 091602](https://github.com/user-attachments/assets/f1603f2a-cb3a-4bb1-96b7-ea62f66df482)

## 📖 How to Contribute

Contributions are welcome!

To contribute:
1. Fork the repository.
2. Create a new branch:
   ```bash
   git checkout -b my-new-feature
   ```
3. Commit your changes:
   ```bash
   git commit -m "add new feature"
   ```
4. Push to the branch:
   ```bash
   git push origin my-new-feature
   ```
5. Open a Pull Request.

## 📜 License
This project is licensed under the **MIT License**. See the [LICENSE](https://github.com/jmsmarcelo/task-tracker-cli-cpp/blob/main/LICENSE) file for details.

## 🙋‍♂️ Author
Created by [Jose Marcelo](https://jmsmarcelo.github.io/). Feel free to get in touch or explore more of my projects!
