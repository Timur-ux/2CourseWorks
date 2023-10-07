#include "Trapezoid.hpp"

bool isPointsValid(std::vector<Point> & points);

void Trapezoid::setBaseParameters() {
    Figure::figureType = "Trapezoid";
    Figure::angles = 4;
}

Trapezoid::Trapezoid(std::vector<Point> &_points) {
    setBaseParameters();
    if(not isPointsValid(_points)) {
        throw new std::invalid_argument("Incorrect point for Trapezoid");
    }
    points = _points;
}

Trapezoid::Trapezoid(std::vector<Point> &&_points) {
    setBaseParameters();
    if(not isPointsValid(_points)) {
        throw new std::invalid_argument("Incorrect point for Trapezoid");
    }
    points = _points;
}

Trapezoid::Trapezoid(const Trapezoid &other) {
    setBaseParameters();
    points = other.getPoints();
}

Trapezoid::Trapezoid(Trapezoid && other) noexcept {
    setBaseParameters();
    points = other.getPoints();
}

Point Trapezoid::getCenter() const
{
    Point diff13 = points[2] - points[0];
    double k1 = diff13.getY() / diff13.getX();

    Point diff24 =  points[3] - points[1];
    double k2 = diff24.getY() / diff24.getX();

    double b1 = points[0].getY() - points[0].getX() * k1;
    double b2 = points[1].getY() - points[1].getX() * k2;

    double crossX = (b1 - b2) / (k2 - k1);
    double crossY = k1 * crossX + b1;

    return Point(decart(crossX, crossY));
}

Trapezoid::operator double() const {
    double a = points[0].getDistance(points[1]);
    double b = points[2].getDistance(points[3]);
    double h = abs(points[0] - points[2]).getY();

    return (a + b) * h / 2; 
}

Figure &Trapezoid::operator=(const Figure &rhs) {
    setBaseParameters();

    points = rhs.getPoints();
    
    return *this; 
}

Figure &Trapezoid::operator=(Figure &&rhs) {
    setBaseParameters();

    points = rhs.getPoints();
    delete &rhs;

    return *this;
}

bool isPointsValid(std::vector<Point> & points) {
    if(points.size() != 4) {
        return false;
    }

    if((points[0] - points[1]).getY() != 0) {
        return false;
    }

    if((points[2] - points[3]).getY() != 0) {
        return false;
    }
    
    return true;
}