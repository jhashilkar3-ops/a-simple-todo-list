#include "hello.hpp"
#include <algorithm>
#include <cctype>
#include <string>


static std::string trim(const std::string& s) {
   size_t start = s.find_first_not_of(" \t\n\r");
   if (start == std::string::npos) return "";
   size_t end = s.find_last_not_of(" \t\n\r");
   return s.substr(start, end - start + 1);
}


static bool iequal(const std::string& a, const std::string& b) {
   if (a.size() != b.size()) return false;
   for (size_t i = 0; i < a.size(); ++i) {
      if (std::tolower((unsigned char)a[i]) != std::tolower((unsigned char)b[i]))
         return false;
   }
   return true;
}

bool TodoList::add(const std::string& description) {
   std::string text = trim(description);


   if (text.empty()) {
      return false;
   }

   for (const Task& t : tasks_) {
      if (!t.completed && iequal(t.description, text)) {
         return false;
      }
   }

   tasks_.emplace_back(text);
   return true;
}

bool TodoList::complete(int index) {
   if (index < 0 || index >= static_cast<int>(tasks_.size())) {
      return false;
   }
   tasks_[index].completed = true;
   return true;
}

std::vector<Task> TodoList::all() const {
   return tasks_;
}

std::vector<Task> TodoList::completed() const {
   std::vector<Task> result;
   for (const Task& t : tasks_) {
      if (t.completed) result.push_back(t);
   }
   return result;
}

std::vector<Task> TodoList::incomplete() const {
   std::vector<Task> result;
   for (const Task& t : tasks_) {
      if (!t.completed) result.push_back(t);
   }
   return result;
}

void TodoList::clear() {
   tasks_.clear();
}

int TodoList::size() const {
   return static_cast<int>(tasks_.size());
}