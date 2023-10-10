#include "Line.hpp"

using namespace geometry;

Line::Line(Point _p1, Point _p2) {
    if(_p1 == _p2) {
        throw new std::invalid_argument("Line need 2 not equal point, equals given");
    }

    p1 = _p1;
    p2 = _p2;

    Point dp = p2 - p1;

    k = (dp.getX() == 0 ? INFINITY : dp.getY() / dp.getX());
    b = (k == INFINITY ? INFINITY : p1.getY() - p1.getX() * k);
}

bool Line::operator||(const Line &rhs) const {
    return k == rhs.k;
}

double geometry::Line::length() {
    return p1.getDistance(p2);
}
