#include <gtest/gtest.h>
#include "Figure.hpp"

using namespace geometry;

TEST(line_tests_set, operator_parallel_test) {
    Line line1(Point(0, 0), Point(1, 2));
    Line line2(Point(0, 1), Point(1, 3));
    Line line3(Point(0, 0), Point(3, 2));

    EXPECT_TRUE(line1 || line2);
    EXPECT_FALSE(line1 || line3);
}

TEST(line_tests_set, get_length_test) {
    Line line(Point(0, 0), Point(1, 2));
    double expectedLenth = sqrt(5);

    EXPECT_TRUE(line.length() == expectedLenth);
}

TEST(line_tests_set, scalarMult_test) {
    Line line1(Point(0, 0), Point(1, 0));
    Line line2(Point(0, 0), Point(0, 1));
    double expectedSCMult = 0;

    EXPECT_TRUE(scalarMult(line1, line2) == expectedSCMult);
}