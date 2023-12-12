#include <gtest/gtest.h>
#include "utils.hpp"

TEST(mathMod, modTest) {
    double width = 10;
    double newX1 = 12.5;
    double newX2 = -7;

    EXPECT_EQ(mathMod(newX1, width), 2.5);
    EXPECT_EQ(mathMod(newX2, width), 3);
}