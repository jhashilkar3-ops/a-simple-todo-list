#ifndef TODOLIST_HPP
#define TODOLIST_HPP
#include <string>
#include <vector>

struct Task {
    std::string description;
    bool completed;

    Task(const std::string& desc)
        : description(desc), completed(false) {}
};

class TodoList {
public:
    bool add(const std::string& description);
    bool complete(int index);
    std::vector<Task> all() const;
    std::vector<Task> completed() const;
    std::vector<Task> incomplete() const;
    void clear();
    int size() const;

private:
    std::vector<Task> tasks_;
};

#endif