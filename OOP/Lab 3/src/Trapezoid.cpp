#include "Trapezoid.hpp"

using namespace geometry;

void Trapezoid::assertPoints(const std::vector<Point> & _points) const {
    if(_points.size() != 4) {
        throw new std::invalid_argument("Incorrect points for Trapezoid");
    }

    Line line1(_points[0], _points[1]);
    Line line2(_points[2], _points[3]);
    if(not (line1 || line2)) {
        throw new std::invalid_argument("Trapezoid must have minimum 1 pair of parallel sides");
    }
}

std::vector<Point> Trapezoid::unificatePoints(std::vector<Point> _points) {
    return Figure::unificatePoints(_points);
}

Trapezoid::Trapezoid() : Figure(4, "Trapezoid") {
    square = 0;
    geometryCenter = Point(0, 0);
}

Trapezoid::Trapezoid(std::vector<Point> &_points) : Trapezoid() {
    points = unificatePoints(_points);
    geometryCenter = calcGeometryCenter(_points);
    square = calcSquare(_points);
}

Trapezoid::Trapezoid(std::vector<Point> &&_points) : Trapezoid() {
    points = unificatePoints(_points);
    geometryCenter = calcGeometryCenter(_points);
    square = calcSquare(_points);
}

Trapezoid::Trapezoid(const Trapezoid &other) : Trapezoid() {
    points = other.getPoints();
    geometryCenter = other.getCenter();
    square = double(other);
}

Trapezoid::Trapezoid(Trapezoid && other) noexcept : Trapezoid() {
    points = other.getPoints();
    geometryCenter = other.getCenter();
    square = double(other);
    
    delete &other;
}

Point Trapezoid::calcGeometryCenter(const std::vector<Point> & _points) const {
    Point diff13 = _points[2] - _points[0];
    double k1 = diff13.getY() / diff13.getX();

    Point diff24 =  _points[3] - _points[1];
    double k2 = diff24.getY() / diff24.getX();

    double b1 = _points[0].getY() - _points[0].getX() * k1;
    double b2 = _points[1].getY() - _points[1].getX() * k2;

    double crossX = (b1 - b2) / (k2 - k1);
    double crossY = k1 * crossX + b1;

    return Point(decart(crossX, crossY));
}

double Trapezoid::calcSquare(const std::vector<Point> & _points) const {
    double a = _points[0].getDistance(_points[1]);
    double b = _points[2].getDistance(_points[3]);
    double h = abs(_points[0] - _points[2]).getY();

    return (a + b) * h / 2; 
}

Figure &Trapezoid::operator=(const Figure &rhs) {
    points = unificatePoints(rhs.getPoints());
    square = double(rhs);
    geometryCenter = rhs.getCenter();

    return *this; 
}

Figure &Trapezoid::operator=(Figure &&rhs) {
    points = unificatePoints(rhs.getPoints());
    square = double(rhs);
    geometryCenter = rhs.getCenter();
    
    delete &rhs;
    return *this;
}

bool Trapezoid::operator==(const Figure &rhs) const {
    std::vector<Point> rhsPoints = rhs.getPoints();
    assertPoints(rhsPoints);

    return double(*this) == double(rhs);
}