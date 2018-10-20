#pragma once

#include <map>

struct counted
{
    struct no_new_instances_guard;

    counted() = delete;
    counted(int data);
    counted(counted const& other);
    ~counted();

    counted& operator=(counted const& c);
    operator int() const;

private:
    int data;

    static std::map<counted const*, int> instances;
};

struct counted::no_new_instances_guard
{
    no_new_instances_guard();

    no_new_instances_guard(no_new_instances_guard const&) = delete;
    no_new_instances_guard& operator=(no_new_instances_guard const&) = delete;

    ~no_new_instances_guard();

    void expect_no_instances();

private:
    std::map<counted const*, int> old_instances;
};