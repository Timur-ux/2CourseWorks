#include <gtest/gtest.h>
#include "Figure.hpp"

using namespace geometry;

TEST(romb_tests_set, constructor_default_test) {
    Romb romb;
    Point expectedPoint;
    bool isValid = true;

    for(Point point : romb.getPoints()) {
        isValid = isValid and (point == expectedPoint);
    }

    EXPECT_TRUE(isValid);
}

TEST(romb_tests_set, constructor_viaVector_test) {
    Point p1(decart(0, 0));
    Point p2(decart(-3, 4));
    Point p3(decart(0, 8));
    Point p4(decart(3, 4));

    
    EXPECT_THROW(Romb({p1});, std::invalid_argument*);
    EXPECT_NO_THROW(Romb({p1, p2, p3, p4}));
}

TEST(romb_tests_set, constructor_viaOtherRomb_test) {
    Point p1(decart(0, 0));
    Point p2(decart(-3, 4));
    Point p3(decart(0, 8));
    Point p4(decart(3, 4));

    Romb romb({p1, p2, p3, p4});
    Romb romb2(romb);
    
    ASSERT_TRUE(romb.getPoints() == romb2.getPoints());
}

TEST(romb_tests_set, get_center_test) {
    Point p1(decart(0, 0));
    Point p2(decart(-3, 4));
    Point p3(decart(0, 8));
    Point p4(decart(3, 4));
    Point expectedCenter(decart(0, 4));

    Romb romb({p1, p2, p3, p4});
    
    ASSERT_TRUE(romb.getCenter() == expectedCenter);
}

TEST(romb_tests_set, get_square_test) {
    Point p1(decart(0, 0));
    Point p2(decart(-3, 4));
    Point p3(decart(0, 8));
    Point p4(decart(3, 4));
    double expectedSquare(24);

    Romb romb({p1, p2, p3, p4});
    
    ASSERT_TRUE(double(romb) == expectedSquare);
}

TEST(romb_tests_set, get_figureType_test) {
    Point p1(decart(0, 0));
    Point p2(decart(-3, 4));
    Point p3(decart(0, 8));
    Point p4(decart(3, 4));
    std::string expectedFigureType = "Romb";

    Romb romb({p1, p2, p3, p4});
    
    ASSERT_TRUE(romb.getFigureType() == expectedFigureType);
}

TEST(romb_tests_set, assign_test) {
    Point p1(decart(0, 0));
    Point p2(decart(-3, 4));
    Point p3(decart(0, 8));
    Point p4(decart(3, 4));
    Romb romb({p1, p2, p3, p4});
    Trapezoid trap({p1, p2, p3, p4});

    Romb assignedRomb = romb;

    ASSERT_TRUE(assignedRomb == romb);
}
