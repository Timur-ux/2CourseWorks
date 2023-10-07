#include <gtest/gtest.h>
#include "Figure.hpp"

TEST(point_test_set, constructor_default_test) {
    Point point;
    
    decart pointCord = point.getDecart();
    decart expectedCourd = decart(0, 0);

    ASSERT_TRUE(pointCord == expectedCourd);
}

TEST(point_test_set, constructor_decart_test) {
    Point point(decart(3, 4));
    
    decart pointCord = point.getDecart();
    decart expectedCourd = decart(3, 4);

    ASSERT_TRUE(pointCord == expectedCourd);
}

TEST(point_test_set, constructor_copy_test) {
    Point point(decart(3, 4));
    
    Point copiedPoint(point);

    ASSERT_TRUE(point.getDecart() == copiedPoint.getDecart());
}

TEST(point_test_set, constructor_move_test) {
    Point point(Point(decart(3, 4)));
    
    decart pos = point.getDecart();
    decart expectedPos = decart(3, 4);

    ASSERT_TRUE(pos == expectedPos);
}

TEST(point_test_set, get_decart_test) {
    decart pos(3, 4);
    Point point(pos);

    decart gettedPos = point.getDecart();

    ASSERT_TRUE(pos == gettedPos);
}

TEST(point_test_set, get_XY_test) {
    decart pos(3, 4);
    Point point(pos);

    double gettedX = point.getX();
    double gettedY = point.getY();

    ASSERT_TRUE(pos.first == gettedX and pos.second == gettedY);
}

TEST(point_test_set, get_distanse_test) {
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

TEST(point_test_set, operator_equal_test) {
    Point point(decart(3, 5));
    
    Point copiedPoint(point);

    ASSERT_TRUE(point == copiedPoint);
}

TEST(point_test_set, operator_plus_test) {
    Point point1(decart(3, 5));
    Point point2(decart(2, 1));
    Point expectedSumPoint(decart(5, 6));

    Point sumPoint = point1 + point2;

    ASSERT_TRUE(sumPoint == expectedSumPoint);
}

TEST(point_test_set, operator_minus_test) {
    Point point1(decart(3, 5));
    Point point2(decart(2, 1));
    Point expectedMinusPoint(decart(1, 4));

    Point minusPoint = point1 - point2;

    ASSERT_TRUE(minusPoint == expectedMinusPoint);
}

TEST(point_test_set, operator_assignCopy_test) {
    Point point(decart(3, 5));
    Point expectedPoint(point);

    Point assignedPoint = point;

    ASSERT_TRUE(assignedPoint == expectedPoint);
}

TEST(point_test_set, operator_assignMove_test) {
    Point expectedPoint(Point(decart(3, 5)));

    Point assignedPoint = Point(decart(3, 5));

    ASSERT_TRUE(assignedPoint == expectedPoint);
}

TEST(point_test_set, operator_abs_test) {
    Point point(decart(-1, -4));
    Point expectedPoint(decart(1, 4));

    Point absPoint = abs(point);

    ASSERT_TRUE(absPoint == expectedPoint);
}

TEST(point_test_set, operator_mult_test) {
    Point point(decart(-1, -4));
    int k = 4;
    Point expectedPoint(decart(-4, -16));

    Point multPointOnK = point * k;
    Point multKOnPoint = k * point;

    ASSERT_TRUE(multKOnPoint == multPointOnK);
    ASSERT_TRUE(multKOnPoint == expectedPoint);
}

TEST(point_test_set, operator_div_test) {
    Point point(decart(-4, -16));
    int k = 4;
    Point expectedPoint(decart(-1, -4));

    Point divvedPoint = point / k;

    ASSERT_TRUE(divvedPoint == expectedPoint);
}

TEST(rectangle_test_set, constructor_viaVector_test) {
    Point p1(decart(1, 3));
    Point p2(decart(5, 2));
    Point p3(decart(1, 13));

    
    EXPECT_THROW(Rectangle(std::vector<Point>{p1});, std::invalid_argument*);
    EXPECT_THROW(Rectangle(std::vector<Point>{p1, p2, p3}), std::invalid_argument*);
    EXPECT_NO_THROW(Rectangle(std::vector<Point>{p1, p2}));
}

TEST(rectangle_test_set, constructor_viaOtherRectangle_test) {
    Point p1(decart(1, 3));
    Point p2(decart(5, 2));

    Rectangle rect(std::vector<Point>{p1, p2});
    Rectangle rect2(rect);
    
    ASSERT_TRUE(rect.getPoints() == rect2.getPoints());
}

TEST(rectangle_test_set, get_center_test) {
    Point p1(decart(1, 3));
    Point p2(decart(5, 2));
    Point expectedCenter(decart(3, 2.5));

    Rectangle rect(std::vector<Point>{p1, p2});
    
    ASSERT_TRUE(rect.getCenter() == expectedCenter);
}

TEST(rectangle_test_set, get_square_test) {
    Point p1(decart(1, 3));
    Point p2(decart(5, 2));
    double expectedSquare(4);

    Rectangle rect(std::vector<Point>{p1, p2});
    
    ASSERT_TRUE(double(rect) == expectedSquare);
}

TEST(rectangle_test_set, assign_test) {
    Point p1(decart(1, 3));
    Point p2(decart(5, 2));
    Rectangle rect = Rectangle(std::vector<Point>{p1, p2});
    
    Rectangle assignedRect = rect;

    ASSERT_TRUE(assignedRect == rect);
}

TEST(trapezoid_test_set, constructor_viaVector_test) {
    Point p1(decart(1, 3));
    Point p2(decart(5, 3));
    Point p3(decart(1, 13));
    Point p4(decart(5, 13));

    
    EXPECT_THROW(Trapezoid(std::vector<Point>{p1});, std::invalid_argument*);
    EXPECT_NO_THROW(Trapezoid(std::vector<Point>{p1, p2, p3, p4}));
}

TEST(trapezoid_test_set, constructor_viaOtherTrapezoid_test) {
    Point p1(decart(1, 3));
    Point p2(decart(5, 3));
    Point p3(decart(1, 13));
    Point p4(decart(5, 13));

    Trapezoid trap(std::vector<Point>{p1, p2, p3, p4});
    Trapezoid trap2(trap);
    
    ASSERT_TRUE(trap.getPoints() == trap2.getPoints());
}

TEST(trapezoid_test_set, get_center_test) {
    Point p1(decart(1, 3));
    Point p2(decart(2, 3));
    Point p3(decart(7, 13));
    Point p4(decart(-1, 13));
    std::vector<Point> points{p1, p2, p3, p4};
    Point expectedCenter(decart(5.0/3, 37.0/9));

    Trapezoid trap(points);
    
    ASSERT_TRUE(trap.getCenter() == expectedCenter);
}

TEST(trapezoid_test_set, get_square_test) {
    Point p1(decart(1, 3));
    Point p2(decart(2, 3));
    Point p4(decart(7, 13));
    Point p3(decart(-1, 13));
    double expectedSquare(45);

    Trapezoid trap(std::vector<Point>{p1, p2, p3, p4});
    
    ASSERT_TRUE(double(trap) == expectedSquare);
}

TEST(trapezoid_test_set, assign_test) {
    Point p1(decart(1, 3));
    Point p2(decart(2, 3));
    Point p3(decart(-1, 13));
    Point p4(decart(7, 13));
    Trapezoid trap(std::vector<Point>{p1, p2, p3, p4});
    
    Trapezoid assignedTrap = trap;

    ASSERT_TRUE(assignedTrap == trap);
}

int main(int argc, char * argw[]) {
    testing::InitGoogleTest(&argc, argw);
    return RUN_ALL_TESTS();
}