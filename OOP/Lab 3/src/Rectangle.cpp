#include "Rectangle.hpp"

using namespace geometry;

geometry::Rectangle::Rectangle() : Figure(4, "Rectangle") {}

Rectangle::Rectangle(std::vector<Point> & _points) : Rectangle() {
	points = _points;
	geometryCenter = calcGeometryCenter(points);
	square = calcSquare(points);
}

Rectangle::Rectangle(std::vector<Point> && _points) : Rectangle() {
	points = _points;
	geometryCenter = calcGeometryCenter(points);
	square = calcSquare(points);
}

Rectangle::Rectangle(const Rectangle & other) : Rectangle() {
	points = other.getPoints();
	geometryCenter = other.getCenter();
	square = double(other);
}

Rectangle::Rectangle(Rectangle && other) noexcept : Rectangle() {
	points = other.getPoints();
	geometryCenter = other.getCenter();
	square = double(other);

	delete & other;
}

Figure & geometry::Rectangle::operator=(const Figure & rhs) {
	Rectangle tmp(rhs.getPoints());
	Swap(tmp);

	return *this;
}

Figure & geometry::Rectangle::operator=(Figure && rhs) noexcept {
	Rectangle tmp(rhs.getPoints());
	Swap(tmp);

	delete & rhs;
	return *this;
}

Point Rectangle::calcGeometryCenter(const std::vector<Point> & _points) const {
	Line diag1(_points[0], _points[2]);
	Line diag2(_points[1], _points[3]);

	return calcCross(diag1, diag2);
}

double Rectangle::calcSquare(const std::vector<Point> & _points) const {
	Point dPoint = abs(_points[0] - _points[2]);
	decart pos = dPoint.getDecart();

	return pos.first * pos.second;
}