#include "Romb.hpp"

using namespace geometry;

Romb::Romb() : Figure(4, "Romb", *(new RombValidator)) {}

Romb::Romb(std::vector<Point> & _points) : Romb() {
    points = unificatePoints(_points);
    validator.validate(points);

    geometryCenter = calcGeometryCenter(points);
    square = calcSquare(points);
}

Romb::Romb(std::vector<Point> && _points) : Romb() {
    points = unificatePoints(_points);
    validator.validate(points);

    geometryCenter = calcGeometryCenter(points);
    square = calcSquare(points);
}

Romb::Romb(const Romb &other) : Romb() {
    points =  other.getPoints();
    geometryCenter = other.getCenter();
    square = double(other);
}

Romb::Romb(Romb &&other) noexcept : Romb() {
    points =  other.getPoints();
    geometryCenter = other.getCenter();
    square = double(other);

    delete &other;
}

Point Romb::calcGeometryCenter(const std::vector<Point> &_points) const {
    Line diag1(_points[0], _points[2]);
    Line diag2(_points[1], _points[3]);

    return calcCross(diag1, diag2);
}

double Romb::calcSquare(const std::vector<Point> & _points) const {
    double d1 = _points[0].getDistance(_points[2]);
    double d2 = _points[1].getDistance(_points[3]);

    return 0.5 * d1 * d2;
}