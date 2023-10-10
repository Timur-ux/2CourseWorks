#include "Rectangle.hpp"

using namespace geometry;

void Rectangle::assertPoints(std::vector<Point> & _points) const {
    if(_points.size() != 4 and _points.size() != 2) {
        throw new std::invalid_argument("Rectangle must have only 2 or 4 base points");
    }
}

std::vector<Point> geometry::Rectangle::unificatePoints(std::vector<Point> _points) {
    if(_points.size() != 2 and _points.size() != 4) {
        throw new std::invalid_argument("Rectangle must have only 2 or 4 base points");
    }

    if(_points.size() == 2) {
        _points.emplace_back(_points[0].getX(), _points[1].getY());
        _points.emplace_back(_points[1].getX(), _points[0].getY());
    }

    std::sort(_points.begin(), _points.end());

    if(_points[0].getY() > _points[1].getY()) {
        std::swap(_points[0], _points[1]);
    }
    if(_points[2].getY() > _points[3].getY()) {
        std::swap(_points[2], _points[3]);
    }

    return _points;
}

geometry::Rectangle::Rectangle() {
    angles = 4;
    square = 0;
    geometryCenter = Point(0, 0);
    figureType = "Rectangle";
}

Rectangle::Rectangle(std::vector<Point> &_points) : Rectangle() {
    points = unificatePoints(_points);
    assertPoints(points);

    geometryCenter = calcGeometryCenter(_points);
    square = calcSquare(_points);
}

Rectangle::Rectangle(std::vector<Point> &&_points) : Rectangle() {
    points = unificatePoints(_points);
    assertPoints(points);

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
    points = unificatePoints(rhs.getPoints());    
    assertPoints(points);

    geometryCenter = rhs.getCenter();
    square = double(rhs);

    return *this;
}
Figure &Rectangle::operator=(Figure &&rhs) {
    points = unificatePoints(rhs.getPoints());    
    assertPoints(points);
    
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