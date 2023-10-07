#include "Rectangle.hpp"
#include "FigureBuilder.hpp"

namespace Figure {
    Rectangle::Rectangle(std::vector<Point> & _points) {
        if(_points.size() != angles) {
            throw new std::invalid_argument("Rectangle must have only 2 base points");
        }
        points = _points;
    }

    void Rectangle::setPoints(std::vector<Point> &_points) {
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
        return static_cast<double>(*this) == static_cast<double>(rhs);
    }

    FigureBuilder *RectangleBuilder::setPoints(std::vector<Point> &_points)
    {
        rectangle->setPoints(_points);

        return this;
    }
    Figure *RectangleBuilder::getFigure()
    {
        return rectangle;
    }
};