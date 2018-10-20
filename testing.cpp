#include "gtest/gtest.h"
#include "optional.h"

TEST(correctness, swap) {
    optional<int> a(123);
    optional<int> b(321);
    swap(a, b);
    EXPECT_TRUE(a == 321 && b == 123);
}

TEST(correctness, clear) {
    optional<std::string> a("hahaha");
    a.clear();
    EXPECT_TRUE(!a);
}

TEST(correctness, swap_empty) {
    optional<int> a;
    optional<int> b(332);
    swap(a, b);
    EXPECT_TRUE(!b && a == 332);
}

TEST(correctness, no_default_constructor) {
    struct A{
        A() = delete;
        int x;
        A(int a) {
            x = a;
        }
    };

    optional<A> opt(123);
    EXPECT_EQ(opt->x, 123);
}

TEST(correctness, self_assignment) {
    optional<int> a(123);
    a = a;
    EXPECT_TRUE(a);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}