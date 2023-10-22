#include <gtest/gtest.h>
#include "Figure.hpp"

TEST(trapezoid_tests_set, constructor_default_test) {
	Trapezoid trap;
	Point expectedPoint;
	bool isValid = true;

	for (Point point : trap.getPoints()) {
		isValid = isValid and (point == expectedPoint);
	}

	EXPECT_TRUE(isValid);
}

TEST(trapezoid_tests_set, constructor_viaVector_test) {
	Point p1(decart(1, 3));
	Point p2(decart(5, 3));
	Point p3(decart(1, 13));
	Point p4(decart(5, 13));


	EXPECT_THROW(Trapezoid({ p1 });, TrapezoidValidatorException);
	EXPECT_NO_THROW(Trapezoid({ p1, p2, p3, p4 }));
}

TEST(trapezoid_tests_set, constructor_viaOtherTrapezoid_test) {
	Point p1(decart(1, 3));
	Point p2(decart(5, 3));
	Point p3(decart(1, 13));
	Point p4(decart(5, 13));

	Trapezoid trap({ p1, p2, p3, p4 });
	Trapezoid trap2(trap);

	ASSERT_TRUE(trap.getPoints() == trap2.getPoints());
}

TEST(trapezoid_tests_set, get_center_test) {
	Point p1(decart(1, 3));
	Point p2(decart(2, 3));
	Point p3(decart(7, 13));
	Point p4(decart(-1, 13));
	std::vector<Point> points{ p1, p2, p3, p4 };
	Point expectedCenter(decart(5.0 / 3, 37.0 / 9));

	Trapezoid trap(points);

	ASSERT_TRUE(trap.getCenter() == expectedCenter);
}

TEST(trapezoid_tests_set, get_square_test) {
	Point p1(decart(1, 3));
	Point p2(decart(2, 3));
	Point p4(decart(7, 13));
	Point p3(decart(-1, 13));
	double expectedSquare(45);

	Figure * trap = new Trapezoid({ p1, p2, p3, p4 });

	ASSERT_TRUE(double(*trap) == expectedSquare);
}

TEST(trapezoid_tests_set, get_figureType_test) {
	Point p1(decart(1, 3));
	Point p2(decart(2, 3));
	Point p4(decart(7, 13));
	Point p3(decart(-1, 13));
	std::string expectedFigureType = "Trapezoid";

	Trapezoid trap({ p1, p2, p3, p4 });

	ASSERT_TRUE(trap.getFigureType() == expectedFigureType);
}

TEST(trapezoid_tests_set, assign_test) {
	Point p1(decart(1, 3));
	Point p2(decart(2, 3));
	Point p3(decart(-1, 13));
	Point p4(decart(7, 13));
	Trapezoid trap({ p1, p2, p3, p4 });

	Trapezoid assignedTrap = trap;

	ASSERT_TRUE(assignedTrap == trap);
}
