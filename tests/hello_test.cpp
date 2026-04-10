#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/hello.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
TEST_CASE("add: adds a valid task", "[add]") {
    TodoList list;
    REQUIRE(list.add("Buy groceries") == true);
    REQUIRE(list.size() == 1);
    REQUIRE(list.all()[0].description == "Buy groceries");
    REQUIRE(list.all()[0].completed == false);
}

TEST_CASE("add: rejects blank task", "[add]") {
    TodoList list;
    REQUIRE(list.add("") == false);
    REQUIRE(list.size() == 0);
}

TEST_CASE("add: rejects whitespace-only task", "[add]") {
    TodoList list;
    REQUIRE(list.add("   ") == false);
    REQUIRE(list.size() == 0);
}

TEST_CASE("add: rejects duplicate incomplete task (case-insensitive)", "[add]") {
    TodoList list;
    list.add("Buy milk");
    REQUIRE(list.add("Buy milk") == false);
    REQUIRE(list.add("BUY MILK") == false);
    REQUIRE(list.size() == 1);
}

TEST_CASE("add: allows duplicate of a completed task", "[add]") {
    TodoList list;
    list.add("Buy milk");
    list.complete(0);
    REQUIRE(list.add("Buy milk") == true);
    REQUIRE(list.size() == 2);
}

TEST_CASE("add: trims leading/trailing whitespace", "[add]") {
    TodoList list;
    list.add("  Walk the dog  ");
    REQUIRE(list.all()[0].description == "Walk the dog");
}

TEST_CASE("complete: marks task at valid index as done", "[complete]") {
    TodoList list;
    list.add("Task A");
    REQUIRE(list.complete(0) == true);
    REQUIRE(list.all()[0].completed == true);
}

TEST_CASE("complete: returns false for negative index", "[complete]") {
    TodoList list;
    list.add("Task A");
    REQUIRE(list.complete(-1) == false);
}

TEST_CASE("complete: returns false for out-of-range index", "[complete]") {
    TodoList list;
    list.add("Task A");
    REQUIRE(list.complete(1) == false);
    REQUIRE(list.complete(99) == false);
}

TEST_CASE("complete: returns false on empty list", "[complete]") {
    TodoList list;
    REQUIRE(list.complete(0) == false);
}

TEST_CASE("all: returns all tasks regardless of status", "[all]") {
    TodoList list;
    list.add("Task A");
    list.add("Task B");
    list.add("Task C");
    list.complete(1);

    auto tasks = list.all();
    REQUIRE(tasks.size() == 3);
}

TEST_CASE("all: returns empty vector when list is empty", "[all]") {
    TodoList list;
    REQUIRE(list.all().empty());
}


TEST_CASE("completed: returns only completed tasks", "[completed]") {
    TodoList list;
    list.add("Task A");
    list.add("Task B");
    list.add("Task C");
    list.complete(0);
    list.complete(2);

    auto done = list.completed();
    REQUIRE(done.size() == 2);
    REQUIRE(done[0].description == "Task A");
    REQUIRE(done[1].description == "Task C");
}

TEST_CASE("completed: returns empty when none are complete", "[completed]") {
    TodoList list;
    list.add("Task A");
    REQUIRE(list.completed().empty());
}


TEST_CASE("incomplete: returns only incomplete tasks", "[incomplete]") {
    TodoList list;
    list.add("Task A");
    list.add("Task B");
    list.add("Task C");
    list.complete(1);

    auto pending = list.incomplete();
    REQUIRE(pending.size() == 2);
    REQUIRE(pending[0].description == "Task A");
    REQUIRE(pending[1].description == "Task C");
}

TEST_CASE("incomplete: returns empty when all are complete", "[incomplete]") {
    TodoList list;
    list.add("Task A");
    list.complete(0);
    REQUIRE(list.incomplete().empty());
}

TEST_CASE("clear: removes all tasks", "[clear]") {
    TodoList list;
    list.add("Task A");
    list.add("Task B");
    list.clear();
    REQUIRE(list.size() == 0);
    REQUIRE(list.all().empty());
}

TEST_CASE("clear: can add tasks again after clearing", "[clear]") {
    TodoList list;
    list.add("Task A");
    list.clear();
    REQUIRE(list.add("Task A") == true);
    REQUIRE(list.size() == 1);
}

TEST_CASE("integration: full workflow", "[integration]") {
    TodoList list;

    list.add("Write report");
    list.add("Send email");
    list.add("Book flight");

    REQUIRE(list.size() == 3);
    REQUIRE(list.incomplete().size() == 3);
    REQUIRE(list.completed().empty());

    list.complete(0);
    list.complete(2);

    REQUIRE(list.incomplete().size() == 1);
    REQUIRE(list.completed().size() == 2);
    REQUIRE(list.incomplete()[0].description == "Send email");
    REQUIRE(list.add("Write report") == true);
    REQUIRE(list.size() == 4);

    list.clear();
    REQUIRE(list.size() == 0);
}