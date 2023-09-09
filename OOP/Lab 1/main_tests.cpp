#include "brackets_check.h"
#include <gtest/gtest.h>

TEST(test_01, basic_test_set) {
    ASSERT_TRUE(brackets_check(""));
}
TEST(test_02, basic_test_set) {
    ASSERT_TRUE(brackets_check("()"));
}
TEST(test_03, basic_test_set) {
    ASSERT_TRUE(brackets_check("()()()()()"));
}
TEST(test_04, basic_test_set) {
    ASSERT_TRUE(brackets_check("((()))()"));
}
TEST(test_05, basic_test_set) {
    ASSERT_FALSE(brackets_check("(()()"));
}
TEST(test_06, basic_test_set) {
    ASSERT_FALSE(brackets_check("(()))"));
}
TEST(test_07, basic_test_set) {
    ASSERT_TRUE(brackets_check("(())(((())))()()"));
}
TEST(test_08, basic_test_set) {
    ASSERT_FALSE(brackets_check("(()"));
}


int main(int argc, char * argw[]) {
    testing::InitGoogleTest(&argc, argw);
    return RUN_ALL_TESTS();
}