#include "Rectangle.hpp"

void Rectangle::setBaseParameters() {
    Figure::figureType = "Rectangle";
    Figure::angles = 2;
}

Rectangle::Rectangle(std::vector<Point> &_points)
{
    setBaseParameters();
    if(_points.size() != angles) {
        throw new std::invalid_argument("Rectangle must have only 2 base points");
    }
    points = _points;
}

Rectangle::Rectangle(std::vector<Point> &&_points) {
    setBaseParameters();
    if(_points.size() != angles) {
        throw new std::invalid_argument("Rectangle must have only 2 base points");
    }

    points = _points;
}

Rectangle::Rectangle(const Rectangle &other) {
    setBaseParameters();
    points = other.getPoints();
}

Rectangle::Rectangle(Rectangle &&other) noexcept {
    setBaseParameters();
    points = other.getPoints();
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
    setBaseParameters();

    points = rhs.getPoints();
    
    return *this;
}
Figure &Rectangle::operator=(Figure &&rhs) {
    setBaseParameters();
    
    points = rhs.getPoints();
    delete &rhs;
    
    return *this;
}