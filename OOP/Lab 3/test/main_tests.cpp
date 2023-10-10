#include <gtest/gtest.h>
#include <fstream>
#include "Figure.hpp"

using namespace geometry;

TEST(point_tests_set, constructor_default_test) {
    Point point;
    
    decart pointCord = point.getDecart();
    decart expectedCourd = decart(0, 0);

    ASSERT_TRUE(pointCord == expectedCourd);
}

TEST(point_tests_set, constructor_XY_test) {
    Point point(3, 4);
    
    decart pointCord = point.getDecart();
    decart expectedCourd = decart(3, 4);

    ASSERT_TRUE(pointCord == expectedCourd);
}

TEST(point_tests_set, constructor_decart_test) {
    Point point(decart(3, 4));
    
    decart pointCord = point.getDecart();
    decart expectedCourd = decart(3, 4);

    ASSERT_TRUE(pointCord == expectedCourd);
}

TEST(point_tests_set, constructor_copy_test) {
    Point point(decart(3, 4));
    
    Point copiedPoint(point);

    ASSERT_TRUE(point.getDecart() == copiedPoint.getDecart());
}

TEST(point_tests_set, constructor_move_test) {
    Point point(Point(decart(3, 4)));
    
    decart pos = point.getDecart();
    decart expectedPos = decart(3, 4);

    ASSERT_TRUE(pos == expectedPos);
}

TEST(point_tests_set, get_decart_test) {
    decart pos(3, 4);
    Point point(pos);

    decart gettedPos = point.getDecart();

    ASSERT_TRUE(pos == gettedPos);
}

TEST(point_tests_set, get_XY_test) {
    decart pos(3, 4);
    Point point(pos);

    double gettedX = point.getX();
    double gettedY = point.getY();

    ASSERT_TRUE(pos.first == gettedX and pos.second == gettedY);
}

TEST(point_tests_set, get_distanse_test) {
    decart pos1(3, 4);
    decart pos2(5, 10);
    Point point1(pos1);
    Point point2(pos2);

    double gettedDistanse1to2 = point1.getDistance(point2);
    double gettedDistanse2to1 = point2.getDistance(point1);
    double expectedDistance =   sqrt(pow(pos1.first - pos2.first, 2) 
                                + pow(pos1.second - pos2.second, 2));

    ASSERT_TRUE(gettedDistanse1to2 == gettedDistanse2to1);
    ASSERT_TRUE(gettedDistanse1to2 == expectedDistance);
}

TEST(point_tests_set, operator_equal_test) {
    Point point(decart(3, 5));
    
    Point copiedPoint(point);

    ASSERT_TRUE(point == copiedPoint);
}

TEST(point_tests_set, operator_plus_test) {
    Point point1(decart(3, 5));
    Point point2(decart(2, 1));
    Point expectedSumPoint(decart(5, 6));

    Point sumPoint = point1 + point2;

    ASSERT_TRUE(sumPoint == expectedSumPoint);
}

TEST(point_tests_set, operator_minus_test) {
    Point point1(decart(3, 5));
    Point point2(decart(2, 1));
    Point expectedMinusPoint(decart(1, 4));

    Point minusPoint = point1 - point2;

    ASSERT_TRUE(minusPoint == expectedMinusPoint);
}

TEST(point_tests_set, operator_assignCopy_test) {
    Point point(decart(3, 5));
    Point expectedPoint(point);

    Point assignedPoint = point;

    ASSERT_TRUE(assignedPoint == expectedPoint);
}

TEST(point_tests_set, operator_assignMove_test) {
    Point expectedPoint(Point(decart(3, 5)));

    Point assignedPoint = Point(decart(3, 5));

    ASSERT_TRUE(assignedPoint == expectedPoint);
}

TEST(point_tests_set, operator_abs_test) {
    Point point(decart(-1, -4));
    Point expectedPoint(decart(1, 4));

    Point absPoint = abs(point);

    ASSERT_TRUE(absPoint == expectedPoint);
}

TEST(point_tests_set, operator_mult_test) {
    Point point(decart(-1, -4));
    int k = 4;
    Point expectedPoint(decart(-4, -16));

    Point multPointOnK = point * k;
    Point multKOnPoint = k * point;

    ASSERT_TRUE(multKOnPoint == multPointOnK);
    ASSERT_TRUE(multKOnPoint == expectedPoint);
}

TEST(point_tests_set, operator_div_test) {
    Point point(decart(-4, -16));
    int k = 4;
    Point expectedPoint(decart(-1, -4));

    Point divvedPoint = point / k;

    ASSERT_TRUE(divvedPoint == expectedPoint);
}

TEST(rectangle_tests_set, constructor_default_test) {
    Rectangle rect;
    Point expectedPoint;
    bool isValid = true;

    for(Point point : rect.getPoints()) {
        isValid = isValid and (point == expectedPoint);
    }

    EXPECT_TRUE(isValid);
}

TEST(rectangle_tests_set, constructor_viaVector_test) {
    Point p1(decart(1, 3));
    Point p2(decart(5, 2));
    Point p3(decart(1, 13));

    
    EXPECT_THROW(Rectangle({p1});, std::invalid_argument*);
    EXPECT_THROW(Rectangle({p1, p2, p3}), std::invalid_argument*);
    EXPECT_NO_THROW(Rectangle({p1, p2}));
}

TEST(rectangle_tests_set, constructor_viaOtherRectangle_test) {
    Point p1(decart(1, 3));
    Point p2(decart(5, 2));

    Rectangle rect({p1, p2});
    Rectangle rect2(rect);
    
    ASSERT_TRUE(rect.getPoints() == rect2.getPoints());
}

TEST(rectangle_tests_set, get_center_test) {
    Point p1(decart(1, 3));
    Point p2(decart(5, 2));
    Point expectedCenter(decart(3, 2.5));

    Rectangle rect({p1, p2});
    
    ASSERT_TRUE(rect.getCenter() == expectedCenter);
}

TEST(rectangle_tests_set, get_square_test) {
    Point p1(decart(1, 3));
    Point p2(decart(5, 2));
    double expectedSquare(4);

    Rectangle rect({p1, p2});
    
    ASSERT_TRUE(double(rect) == expectedSquare);
}

TEST(rectangle_tests_set, get_figureType_test) {
    Point p1(decart(1, 3));
    Point p2(decart(5, 2));
    std::string expectedType = "Rectangle";

    Rectangle rect({p1, p2});
    
    ASSERT_TRUE(rect.getFigureType() == expectedType);
}

TEST(rectangle_tests_set, assign_test) {
    Point p1(decart(1, 3));
    Point p2(decart(5, 2));
    Rectangle rect = Rectangle({p1, p2});
    
    Rectangle assignedRect = rect;

    ASSERT_TRUE(assignedRect == rect);
}

TEST(trapezoid_tests_set, constructor_default_test) {
    Trapezoid trap;
    Point expectedPoint;
    bool isValid = true;

    for(Point point : trap.getPoints()) {
        isValid = isValid and (point == expectedPoint);
    }

    EXPECT_TRUE(isValid);
}

TEST(trapezoid_tests_set, constructor_viaVector_test) {
    Point p1(decart(1, 3));
    Point p2(decart(5, 3));
    Point p3(decart(1, 13));
    Point p4(decart(5, 13));

    
    EXPECT_THROW(Trapezoid({p1});, std::invalid_argument*);
    EXPECT_NO_THROW(Trapezoid({p1, p2, p3, p4}));
}

TEST(trapezoid_tests_set, constructor_viaOtherTrapezoid_test) {
    Point p1(decart(1, 3));
    Point p2(decart(5, 3));
    Point p3(decart(1, 13));
    Point p4(decart(5, 13));

    Trapezoid trap({p1, p2, p3, p4});
    Trapezoid trap2(trap);
    
    ASSERT_TRUE(trap.getPoints() == trap2.getPoints());
}

TEST(trapezoid_tests_set, get_center_test) {
    Point p1(decart(1, 3));
    Point p2(decart(2, 3));
    Point p3(decart(7, 13));
    Point p4(decart(-1, 13));
    std::vector<Point> points{p1, p2, p3, p4};
    Point expectedCenter(decart(5.0/3, 37.0/9));

    Trapezoid trap(points);
    
    ASSERT_TRUE(trap.getCenter() == expectedCenter);
}

TEST(trapezoid_tests_set, get_square_test) {
    Point p1(decart(1, 3));
    Point p2(decart(2, 3));
    Point p4(decart(7, 13));
    Point p3(decart(-1, 13));
    double expectedSquare(45);

    Figure* trap = new Trapezoid({p1, p2, p3, p4});
    
    ASSERT_TRUE(double(*trap) == expectedSquare);
}

TEST(trapezoid_tests_set, get_figureType_test) {
    Point p1(decart(1, 3));
    Point p2(decart(2, 3));
    Point p4(decart(7, 13));
    Point p3(decart(-1, 13));
    std::string expectedFigureType = "Trapezoid";

    Trapezoid trap({p1, p2, p3, p4});
    
    ASSERT_TRUE(trap.getFigureType() == expectedFigureType);
}

TEST(trapezoid_tests_set, assign_test) {
    Point p1(decart(1, 3));
    Point p2(decart(2, 3));
    Point p3(decart(-1, 13));
    Point p4(decart(7, 13));
    Trapezoid trap({p1, p2, p3, p4});
    
    Trapezoid assignedTrap = trap;

    ASSERT_TRUE(assignedTrap == trap);
}

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
    
    Romb assignedTrap = romb;

    ASSERT_TRUE(assignedTrap == romb);
}

int main(int argc, char * argw[]) {
    testing::InitGoogleTest(&argc, argw);
    return RUN_ALL_TESTS();
}