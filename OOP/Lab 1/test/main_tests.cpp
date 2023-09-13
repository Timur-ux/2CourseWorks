#include "isBracketsValid.h"
#include <gtest/gtest.h>

TEST(test_01, basic_test_set) {

    std::string string_to_test = "";

    bool isValid = isBracketsValid(string_to_test);

    ASSERT_TRUE(isValid);
}
TEST(test_02, basic_test_set) {
    std::string string_to_test = "()";

    bool isValid = isBracketsValid(string_to_test);

    ASSERT_TRUE(isValid);
}
TEST(test_03, basic_test_set) {
    std::string string_to_test = "()()()()()";

    bool isValid = isBracketsValid(string_to_test);

    ASSERT_TRUE(isValid);
}
TEST(test_04, basic_test_set) {
    std::string string_to_test = "((()))()";

    bool isValid = isBracketsValid(string_to_test);

    ASSERT_TRUE(isValid);
}
TEST(test_05, basic_test_set) {
    std::string string_to_test = "(()()";

    bool isValid = isBracketsValid(string_to_test);
    ASSERT_FALSE(isValid);
}
TEST(test_06, basic_test_set) {
    std::string string_to_test = "(()))";

    bool isValid = isBracketsValid(string_to_test);

    ASSERT_FALSE(isValid);
}
TEST(test_07, basic_test_set) {
    std::string string_to_test = "(())(((())))()()";

    bool isValid = isBracketsValid(string_to_test);

    ASSERT_TRUE(isValid);
}
TEST(test_08, basic_test_set) {
    std::string string_to_test = "(()";

    bool isValid = isBracketsValid(string_to_test);

    ASSERT_FALSE(isValid);
}


int main(int argc, char * argw[]) {
    testing::InitGoogleTest(&argc, argw);
    return RUN_ALL_TESTS();
}