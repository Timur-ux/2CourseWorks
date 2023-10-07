#include "Rectangle.hpp"

Rectangle::Rectangle(std::vector<Point> & _points) {
    if(_points.size() != angles) {
        throw new std::invalid_argument("Rectangle must have only 2 base points");
    }
    points = _points;
}

Rectangle::Rectangle(std::vector<Point> &&_points) {
    Figure::figureType = "Rectangle";
    Figure::angles = 2;
    if(_points.size() != angles) {
        throw new std::invalid_argument("Rectangle must have only 2 base points");
    }

    points = _points;
}

Point Rectangle::getCenter() const
{
    return (points[0] + points[1]) / 2.0;
}

Rectangle::operator double() const {
    Point dPoint = abs(points[0] - points[1]);
    decart pos = dPoint.getDecart();
    
    return pos.first * pos.second;
}
Figure &Rectangle::operator=(const Figure &rhs) {
    points = rhs.getPoints();
    
    return *this;
}
Figure &Rectangle::operator=(Figure &&rhs) {
    points = rhs.getPoints();
    delete &rhs;
    
    return *this;
}
bool Rectangle::operator==(const Figure &rhs) const {
    return double(*this) == double(rhs);
}