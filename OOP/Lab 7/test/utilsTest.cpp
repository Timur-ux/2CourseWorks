#include <gtest/gtest.h>
#include "utils.hpp"

TEST(UtilsTestSet, mathModTest) {
    double mod = 10;
    double val1 = -1;
    double val2 = -1.5;
    double val3 = 12;

    EXPECT_EQ(mathMod(val1, mod), 9);
    EXPECT_EQ(mathMod(val2, mod), 8.5);
    EXPECT_EQ(mathMod(val3, mod), 2);
}