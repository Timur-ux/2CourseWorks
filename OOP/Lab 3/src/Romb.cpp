#include "Romb.hpp"

bool isParallel(std::vector<Point> & _points);

void Romb::setBaseParameters() {
    Figure::figureType = "Romb";
    Figure::angles = 4;
}

Romb::Romb(std::vector<Point> &_points) {
    setBaseParameters();

    if(_points.size() != 4 or not isParallel(_points)) {
        throw new std::invalid_argument("Incrrect points for Romb");
    }

    points = _points;
}

Romb::Romb(std::vector<Point> &&_points) {
    setBaseParameters();

    if(_points.size() != 4 or not isParallel(_points)) {
        throw new std::invalid_argument("Incrrect points for Romb");
    }

    points = _points;
}

Romb::Romb(const Romb &other) {
    setBaseParameters();

    points = other.points;
}

Romb::Romb(Romb &&other) noexcept {
    setBaseParameters();

    points = other.points;
}

Point Romb::getCenter() const {
    return (points[0] + points[2]) / 2;
}

Romb::operator double() const {
    double d1 = points[0].getDistance(points[2]);
    double d2 = points[1].getDistance(points[3]);

    return 0.5 * d1 * d2;
}

bool isParallel(std::vector<Point>& points) {
    if(points.size() != 4) {
        throw new std::invalid_argument("isParallel need 4 points exactly");
    }

    Point line1 = (points[0] - points[1]);
    double k1 = line1.getY() / line1.getX();
    
    Point line2 = (points[3] - points[2]);
    double k2 = line2.getY() / line2.getX();

    return abs(k1 - k2) < EPS;
}

Figure &Romb::operator=(const Figure &rhs) {
    setBaseParameters();

    points = rhs.getPoints();

    return *this;
}

Figure &Romb::operator=(Figure &&rhs) {
    setBaseParameters();
    
    points = rhs.getPoints();
    delete &rhs;

    return *this;
}
