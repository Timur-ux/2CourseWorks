#include "Romb.hpp"

using namespace geometry;

void Romb::assertPoints(const std::vector<Point> & _points) const {
    if(_points.size() != 4) {
        throw new std::invalid_argument("Romb must have 4 points");
    }

    Line line1(_points[0], _points[1]);
    Line line2(_points[1], _points[2]);
    Line line3(_points[2], _points[3]);
    Line line4(_points[3], _points[0]);

    if(not(line1 || line3) or not(line2 || line4)) {
        throw new std::invalid_argument("Romb must have 2 pairs of parallel sides, unparallel given");
    }
}

std::vector<Point> geometry::Romb::unificatePoints(std::vector<Point> _points) {
    return Figure::unificatePoints(_points);
}

Romb::Romb() : Figure(4, "Romb") {
    square = 0;
    geometryCenter = Point(0, 0);
}

Romb::Romb(std::vector<Point> & _points) : Romb() {
    points = unificatePoints(_points);
    geometryCenter = calcGeometryCenter(_points);
    square = calcSquare(_points);
}

Romb::Romb(std::vector<Point> && _points) : Romb() {
    points = unificatePoints(_points);
    geometryCenter = calcGeometryCenter(_points);
    square = calcSquare(_points);
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

Figure &Romb::operator=(const Figure &rhs) {
    points = unificatePoints(rhs.getPoints());
    geometryCenter = rhs.getCenter();
    square = double(rhs);

    return *this;
}

Figure &Romb::operator=(Figure &&rhs) {
    points = unificatePoints(rhs.getPoints());
    geometryCenter = rhs.getCenter();
    square = double(rhs);

    delete &rhs;
    return *this;
}

bool Romb::operator==(const Figure &rhs) const {
    std::vector<Point> rhsPoints = rhs.getPoints();
    assertPoints(rhsPoints);
    
    return double(*this) == double(rhs);
}


Point Romb::calcGeometryCenter(const std::vector<Point> &_points) const {
    return (_points[0] + _points[2]) / 2;
}

double Romb::calcSquare(const std::vector<Point> & _points) const {
    double d1 = _points[0].getDistance(_points[2]);
    double d2 = _points[1].getDistance(_points[3]);

    return 0.5 * d1 * d2;
}