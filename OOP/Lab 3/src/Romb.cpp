#include "Romb.hpp"

using namespace geometry;

bool isParallel(const std::vector<Point> & _points);

void geometry::Romb::assertPoints(const std::vector<Point> &_points) const {
    if(not isParallel(_points)) {
        throw new std::invalid_argument("Incrrect points for Romb");
    }
}

geometry::Romb::Romb() {
    angles = 4;
    square = 0;
    geometryCenter = Point(0, 0);
    figureType = "Romb";
}

Romb::Romb(std::vector<Point> & _points) : Romb() {
    assertPoints(_points);
    points = _points;
    geometryCenter = calcGeometryCenter(_points);
    square = calcSquare(_points);
}

Romb::Romb(std::vector<Point> && _points) : Romb() {
    assertPoints(_points);
    points = _points;
    geometryCenter = calcGeometryCenter(_points);
    square = calcSquare(_points);
}

Romb::Romb(const Romb &other) {
    std::vector<Point> otherPoints =  other.getPoints();
    
    assertPoints(otherPoints);
    points = otherPoints;
    geometryCenter = calcGeometryCenter(otherPoints);
    square = calcSquare(otherPoints);
}

Romb::Romb(Romb &&other) noexcept {
    std::vector<Point> otherPoints =  other.getPoints();
    
    assertPoints(otherPoints);
    points = otherPoints;
    geometryCenter = calcGeometryCenter(otherPoints);
    square = calcSquare(otherPoints);

    delete &other;
}

Figure &Romb::operator=(const Figure &rhs) {
    std::vector<Point> rhsPoints = rhs.getPoints();
    assertPoints(rhsPoints);
    
    points = rhsPoints;
    geometryCenter = rhs.getCenter();
    square = double(rhs);

    return *this;
}

Figure &Romb::operator=(Figure &&rhs) {
    std::vector<Point> rhsPoints = rhs.getPoints();
    assertPoints(rhsPoints);
    
    points = rhsPoints;
    geometryCenter = rhs.getCenter();
    square = double(rhs);

    delete &rhs;
    return *this;
}

bool geometry::Romb::operator==(const Figure &rhs) const {
    assertPoints(rhs.getPoints());
    return double(*this) == double(rhs);
}

bool isParallel(const std::vector<Point>& points) {
    if(points.size() != 4) {
        throw new std::invalid_argument("isParallel need 4 points exactly");
    }

    Point line1 = (points[0] - points[1]);
    double k1 = line1.getY() / line1.getX();
    
    Point line2 = (points[3] - points[2]);
    double k2 = line2.getY() / line2.getX();

    return abs(k1 - k2) < EPS;
}

Point Romb::calcGeometryCenter(const std::vector<Point> & _points) const {
    return (_points[0] + _points[2]) / 2;
}

double Romb::calcSquare(const std::vector<Point> & _points) const {
    double d1 = _points[0].getDistance(_points[2]);
    double d2 = _points[1].getDistance(_points[3]);

    return 0.5 * d1 * d2;
}