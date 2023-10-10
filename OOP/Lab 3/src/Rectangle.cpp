#include "Rectangle.hpp"

using namespace geometry;

void geometry::Rectangle::assertPoints(const std::vector<Point> & _points) const {
    if(_points.size() != angles) {
        throw new std::invalid_argument("Rectangle must have only 2 base points");
    }
}

geometry::Rectangle::Rectangle() {
    angles = 2;
    // square = 0;
    // geometryCenter = Point(0, 0);
    figureType = "Rectangle";
}

Rectangle::Rectangle(std::vector<Point> &_points) : Rectangle()
{
    assertPoints(_points);
    points = _points;
    geometryCenter = calcGeometryCenter(_points);
    square = calcSquare(_points);
}

Rectangle::Rectangle(std::vector<Point> &&_points) : Rectangle() {
    assertPoints(_points);
    points = _points;
    geometryCenter = calcGeometryCenter(_points);
    square = calcSquare(_points);
}

Rectangle::Rectangle(const Rectangle &other) : Rectangle() {
    points = other.getPoints();
    geometryCenter = other.getCenter();
    square = double(other);
}

Rectangle::Rectangle(Rectangle &&other) noexcept {
    points = other.getPoints();
    geometryCenter = other.getCenter();
    square = double(other);
    
    delete &other;
}

Figure &Rectangle::operator=(const Figure &rhs) {
    
    std::vector<Point> rhsPoints = rhs.getPoints();
    assertPoints(rhsPoints);

    points = rhsPoints;
    geometryCenter = rhs.getCenter();
    square = double(rhs);

    return *this;
}
Figure &Rectangle::operator=(Figure &&rhs) {
    
    std::vector<Point> rhsPoints = rhs.getPoints();
    assertPoints(rhsPoints);

    points = rhsPoints;
    geometryCenter = rhs.getCenter();
    square = double(rhs);
    
    delete &rhs;
    return *this;
}

bool geometry::Rectangle::operator==(const Figure &rhs) const  {
    std::vector<Point> rhsPoints = rhs.getPoints();
    assertPoints(rhsPoints);
    return double(*this) == double(rhs);
}

Point Rectangle::calcGeometryCenter(const std::vector<Point> & _points) const {
    return (_points[0] + _points[1]) / 2.0;
}

double Rectangle::calcSquare(const std::vector<Point> & _points) const {
    Point dPoint = abs(_points[0] - _points[1]);
    decart pos = dPoint.getDecart();
    
    return pos.first * pos.second;
}