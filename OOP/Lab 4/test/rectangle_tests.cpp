#include <gtest/gtest.h>
#include "Figure.hpp"

TEST(rectangle_tests_set, constructor_default_test) {
	Rectangle rect;
	Point expectedPoint;
	bool isValid = true;

	for (Point point : rect.getPoints()) {
		isValid = isValid and (point == expectedPoint);
	}

	EXPECT_TRUE(isValid);
}

TEST(rectangle_tests_set, constructor_viaVector_test) {
	Point p1(decart(1, 3));
	Point p2(decart(5, 3));
	Point p3(decart(1, 13));
	Point p4(decart(5, 13));


	EXPECT_THROW(Rectangle({ p1 });, RectangleValidatorException);
	EXPECT_THROW(Rectangle({ p1, p2, p3 }), RectangleValidatorException);
	EXPECT_NO_THROW(Rectangle({ p1, p2, p3, p4 }));
}

TEST(rectangle_tests_set, constructor_viaOtherRectangle_test) {
	Point p1(decart(1, 3));
	Point p2(decart(5, 2));
	Point p3(decart(5, 3));
	Point p4(decart(1, 2));

	Rectangle rect({ p1, p2, p3, p4 });
	Rectangle rect2(rect);

	ASSERT_TRUE(rect.getPoints() == rect2.getPoints());
}

TEST(rectangle_tests_set, get_center_test) {
	Point p1(decart(1, 3));
	Point p2(decart(5, 2));
	Point p3(decart(5, 3));
	Point p4(decart(1, 2));
	Point expectedCenter(decart(3, 2.5));

	Rectangle rect({ p1, p2, p3, p4 });

	ASSERT_TRUE(rect.getCenter() == expectedCenter);
}

TEST(rectangle_tests_set, get_square_test) {
	Point p1(decart(1, 3));
	Point p2(decart(5, 2));
	Point p3(decart(5, 3));
	Point p4(decart(1, 2));
	double expectedSquare(4);

	Rectangle rect({ p1, p2, p3, p4 });

	ASSERT_TRUE(double(rect) == expectedSquare);
}

TEST(rectangle_tests_set, get_figureType_test) {
	Point p1(decart(1, 3));
	Point p2(decart(5, 2));
	Point p3(decart(5, 3));
	Point p4(decart(1, 2));
	std::string expectedType = "Rectangle";

	Rectangle rect({ p1, p2, p3, p4 });

	ASSERT_TRUE(rect.getFigureType() == expectedType);
}

TEST(rectangle_tests_set, assign_test) {
	Point p1(decart(1, 3));
	Point p2(decart(5, 2));
	Point p3(decart(5, 3));
	Point p4(decart(1, 2));
	Rectangle rect = Rectangle({ p1, p2, p3, p4 });

	Rectangle assignedRect = rect;

	ASSERT_TRUE(assignedRect == rect);
}
