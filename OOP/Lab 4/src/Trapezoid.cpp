#include "Trapezoid.hpp"

using namespace geometry;

Trapezoid::Trapezoid() : Figure(4, "Trapezoid", *(new TrapezoidValidator)) {}

Trapezoid::Trapezoid(std::vector<Point> &_points) : Trapezoid() {
    points = unificatePoints(_points);
    validator.validate(points);

    geometryCenter = calcGeometryCenter(points);
    square = calcSquare(points);
}

Trapezoid::Trapezoid(std::vector<Point> &&_points) : Trapezoid() {
    points = unificatePoints(_points);
    validator.validate(points);

    geometryCenter = calcGeometryCenter(points);
    square = calcSquare(points);
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
}

Point Trapezoid::calcGeometryCenter(const std::vector<Point> & _points) const {
    Line diag1(_points[0], _points[2]);
    Line diag2(_points[1], _points[3]);

    return calcCross(diag1, diag2);
}

double Trapezoid::calcSquare(const std::vector<Point> & _points) const {
    double a = _points[0].getDistance(_points[1]);
    double b = _points[2].getDistance(_points[3]);
    double h = abs(_points[0] - _points[2]).getY();

    return (a + b) * h / 2; 
}