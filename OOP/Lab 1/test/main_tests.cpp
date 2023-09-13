#include "isBracketsValid.h"
#include <gtest/gtest.h>

TEST(test_01, basic_test_set) {

    std::string string_to_test = "";

    bool chek = brackets_check(string_to_test);

    ASSERT_TRUE(chek);
}
TEST(test_02, basic_test_set) {
    std::string string_to_test = "()";

    bool chek = brackets_check(string_to_test);

    ASSERT_TRUE(chek);
}
TEST(test_03, basic_test_set) {
    std::string string_to_test = "()()()()()";

    bool chek = brackets_check(string_to_test);

    ASSERT_TRUE(chek);
}
TEST(test_04, basic_test_set) {
    std::string string_to_test = "((()))()";

    bool chek = brackets_check(string_to_test);

    ASSERT_TRUE(chek);
}
TEST(test_05, basic_test_set) {
    std::string string_to_test = "(()()";

    bool chek = brackets_check(string_to_test);
    ASSERT_FALSE(chek);
}
TEST(test_06, basic_test_set) {
    std::string string_to_test = "(()))";

    bool chek = brackets_check(string_to_test);

    ASSERT_FALSE(chek);
}
TEST(test_07, basic_test_set) {
    std::string string_to_test = "(())(((())))()()";

    bool chek = brackets_check(string_to_test);

    ASSERT_TRUE(chek);
}
TEST(test_08, basic_test_set) {
    std::string string_to_test = "(()";

    bool chek = brackets_check(string_to_test);

    ASSERT_FALSE(chek);
}


int main(int argc, char * argw[]) {
    testing::InitGoogleTest(&argc, argw);
    return RUN_ALL_TESTS();
}