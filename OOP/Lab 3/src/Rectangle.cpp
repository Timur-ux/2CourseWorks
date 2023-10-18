#include "Rectangle.hpp"

using namespace geometry;

void Rectangle::assertPoints(const std::vector<Point> & _points) const {
    if(_points.size() != 4) {
        throw new std::invalid_argument("Rectangle must have only 4 points");
    }
     
    Line line1(_points[0], _points[1]);
    Line line2(_points[1], _points[2]);
    Line line3(_points[2], _points[3]);
    Line line4(_points[3], _points[0]);

    if(not((line1 || line3) and (line2 || line4))) {
        throw new std::invalid_argument("Rectangle must have 2 pairs of parallels line, unparallel given");
    }

    if( 
        scalarMult(line1, line2) > EPS or 
        scalarMult(line2, line3) > EPS or
        scalarMult(line3, line4) > EPS or
        scalarMult(line4, line1) > EPS
      ) {
        throw new std::invalid_argument("Rectangle must have ortogonal sides");
    }
}

std::vector<Point> geometry::Rectangle::unificatePoints(std::vector<Point> _points) {
    if(_points.size() == 2) {
        _points.emplace_back(_points[0].getX(), _points[1].getY());
        _points.emplace_back(_points[1].getX(), _points[0].getY());
    }

    return Figure::unificatePoints(_points);
}

geometry::Rectangle::Rectangle() : Figure(4, "Rectangle") {
    square = 0;
    geometryCenter = Point(0, 0);
}

Rectangle::Rectangle(std::vector<Point> &_points) : Rectangle() {
    points = unificatePoints(_points);
    geometryCenter = calcGeometryCenter(_points);
    square = calcSquare(_points);
}

Rectangle::Rectangle(std::vector<Point> &&_points) : Rectangle() {
    points = unificatePoints(_points);
    geometryCenter = calcGeometryCenter(_points);
    square = calcSquare(_points);
}

Rectangle::Rectangle(const Rectangle &other) : Rectangle() {
    points = other.getPoints();
    geometryCenter = other.getCenter();
    square = double(other);
}

Rectangle::Rectangle(Rectangle &&other) noexcept : Rectangle() {
    points = other.getPoints();
    geometryCenter = other.getCenter();
    square = double(other);
    
    delete &other;
}

Figure &Rectangle::operator=(const Figure &rhs) {
    points = unificatePoints(rhs.getPoints());    
    geometryCenter = rhs.getCenter();
    square = double(rhs);

    return *this;
}
Figure &Rectangle::operator=(Figure &&rhs) {
    points = unificatePoints(rhs.getPoints());
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