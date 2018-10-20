#include "counted.h"
#include <gtest/gtest.h>

counted::counted(int data)
        : data(data)
{
    auto p = instances.insert({this, data});
    EXPECT_TRUE(p.second);
}

counted::counted(counted const& other)
        : data(other.data)
{
    auto p = instances.insert({this, data});
    EXPECT_TRUE(p.second);
}

counted::~counted()
{
    size_t n = instances.erase(this);
    EXPECT_EQ(1u, n);
}

counted& counted::operator=(counted const& c)
{
    auto it = instances.find(this);
    EXPECT_TRUE(it != instances.end());
    EXPECT_EQ(it->second, data);

    data = c.data;
    return *this;
}

counted::operator int() const
{
    auto it = instances.find(this);
    EXPECT_TRUE(it != instances.end());
    EXPECT_EQ(it->second, data);

    return data;
}

std::map<counted const*, int> counted::instances;

counted::no_new_instances_guard::no_new_instances_guard()
        : old_instances(instances)
{}

counted::no_new_instances_guard::~no_new_instances_guard()
{
    EXPECT_TRUE(old_instances == instances);
}

void counted::no_new_instances_guard::expect_no_instances()
{
    EXPECT_TRUE(old_instances == instances);
}
