#include <iostream>
#include "src/hello.hpp"
#include <string>


void printTasks(const std::vector<Task>& tasks, const std::string& header) {
    std::cout << "\n--- " << header << " ---\n";
    if (tasks.empty()) {
        std::cout << "  (none)\n";
        return;
    }
    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << "  [" << (tasks[i].completed ? "X" : " ") << "] "
                  << tasks[i].description << "\n";
    }
}

void showMenu() {
    std::cout << "\nOptions:\n"
              << "  1. Add task\n"
              << "  2. Complete a task\n"
              << "  3. View all tasks\n"
              << "  4. View incomplete tasks\n"
              << "  5. View completed tasks\n"
              << "  6. Clear all tasks\n"
              << "  7. Quit\n"
              << "Choice: ";
}

int main() {
    TodoList list;
    int choice = 0;

    std::cout << "=== Todo List Manager ===\n";

    while (true) {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(); // consume newline

        if (choice == 1) {
            std::cout << "Enter task: ";
            std::string task;
            std::getline(std::cin, task);
            if (list.add(task)) {
                std::cout << "Task added.\n";
            } else {
                std::cout << "Could not add task: blank or duplicate incomplete task.\n";
            }

        } else if (choice == 2) {
            printTasks(list.incomplete(), "Incomplete Tasks");
            if (list.incomplete().empty()) continue;

            std::cout << "Enter task number to complete (from full list, 1-based): ";
            int idx;
            std::cin >> idx;
            std::cin.ignore();
            if (list.complete(idx - 1)) {
                std::cout << "Task marked complete.\n";
            } else {
                std::cout << "Invalid task number.\n";
            }

        } else if (choice == 3) {
            printTasks(list.all(), "All Tasks");

        } else if (choice == 4) {
            printTasks(list.incomplete(), "Incomplete Tasks");

        } else if (choice == 5) {
            printTasks(list.completed(), "Completed Tasks");

        } else if (choice == 6) {
            list.clear();
            std::cout << "All tasks cleared.\n";

        } else if (choice == 7) {
            std::cout << "Goodbye!\n";
            break;

        } else {
            std::cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}