#include "Figure.hpp"

using namespace geometry;



Figure::Figure(int _angles, std::string _figureType)
	: angles(_angles)
	, figureType(_figureType)
	, square(0)
	, geometryCenter(0, 0) {
}

void geometry::Figure::Swap(const Figure & other) {
	points = other.points;
	square = other.square;
	geometryCenter = other.geometryCenter;
}

std::vector<Point> Figure::getPoints() const {
	return points;
}

int Figure::getAngles() const {
	return angles;
}

std::string geometry::Figure::getFigureType() const {
	return figureType;
}

Point Figure::getCenter() const {
	return geometryCenter;
}

geometry::Figure::operator double() const {
	return square;
}

bool geometry::Figure::operator==(const Figure & rhs) const {
	std::vector<Point> rhsPoints = rhs.getPoints();

	return typeid(*this) == typeid(rhs) && double(*this) == double(rhs);
}

std::ostream & geometry::operator<<(std::ostream & os, const Figure & figure) {
	std::vector<Point> points = figure.getPoints();

	os << figure.getFigureType() << ": [ ";
	for (Point point : figure.getPoints()) {
		os << point << ' ';
	}
	os << ']' << std::endl;
	os << "Geometry center = " << figure.getCenter() << std::endl;
	os << "Square = " << double(figure) << std::endl;

	return os;
}