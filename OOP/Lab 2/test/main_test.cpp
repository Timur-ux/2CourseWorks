#include "Octal.hpp"
#include <gtest/gtest.h>

TEST(test_get, basic_metods_set) {

    Octal octal("12345670");
    string sOctal = "12345670";

    bool cmp = (octal.get() == sOctal);

    ASSERT_TRUE(cmp);
}

TEST(test_size, basic_metods_set) {

    string sOctal = "12345670";
    Octal octal(sOctal);

    bool cmp = (octal.size() == sOctal.size());

    ASSERT_TRUE(cmp);
}

TEST(test_copy, basic_metods_set) {

    string sOctal = "12345670";
    Octal octal(sOctal);

    bool cmp = (octal.get() == octal.copy().get());

    ASSERT_TRUE(cmp);
}

TEST(test_equal, relations_test_set) {

    string sOctal = "12345670";
    Octal firstOctal(sOctal);
    Octal secondOctal(sOctal);

    bool cmp = (firstOctal == secondOctal);

    ASSERT_TRUE(cmp);
}

TEST(test_greater, relations_test_set) {

    string sFirstOctal = "123";
    string sSecondOctal = "13";
    Octal firstOctal(sFirstOctal);
    Octal secondOctal(sSecondOctal);

    bool cmp = (firstOctal > secondOctal);

    ASSERT_TRUE(cmp);
}

TEST(test_lesser, relations_test_set) {

    string sFirstOctal = "123";
    string sSecondOctal = "13";
    Octal firstOctal(sFirstOctal);
    Octal secondOctal(sSecondOctal);

    bool cmp = (firstOctal < secondOctal);

    ASSERT_FALSE(cmp);
}

TEST(test_initializer_list, basic_creating_set) {

    Octal firstOctal("123");
    Octal secondOctal{'1', '2', '3'};

    bool cmp = (firstOctal == secondOctal);

    ASSERT_TRUE(cmp);
}

TEST(test_with_string, assingn_test_set) {

    string sOctal = "12345670";
    Octal octal = sOctal;

    bool cmp = (octal.get() == sOctal);

    ASSERT_TRUE(cmp);
}

TEST(test_with_LinkOctal, assingn_test_set) {

    string sOctal = "12345670";
    Octal firstOctal(sOctal);
    Octal secondOctal = firstOctal;

    bool cmp = (firstOctal == secondOctal);

    ASSERT_TRUE(cmp);
}

TEST(test_with_DoubleLinkOctal, assingn_test_set) {

    string sOctal = "12345670";
    Octal octal = Octal(sOctal);

    bool cmp = (octal.get() == sOctal);

    ASSERT_TRUE(cmp);
}

TEST(test_addition, operations_test_set) {

    Octal firstOctal("123");
    Octal secondOctal("17");
    Octal resultOctal("142");

    bool cmp = (firstOctal + secondOctal == resultOctal);

    ASSERT_TRUE(cmp);
}

TEST(test_substraction, operations_test_set) {

    Octal firstOctal("142");
    Octal secondOctal("17");
    Octal resultOctal("123");

    bool cmp = (firstOctal - secondOctal == resultOctal);

    ASSERT_TRUE(cmp);
}

int main(int argc, char * argw[]) {
    testing::InitGoogleTest(&argc, argw);
    return RUN_ALL_TESTS();
}