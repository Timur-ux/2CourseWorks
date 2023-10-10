#include "Line.hpp"

using namespace geometry;

Line::Line(Point _p1, Point _p2) {
    if(_p1 == _p2) {
        throw new std::invalid_argument("Line need 2 not equal point, equals given");
    }

    p1 = _p1;
    p2 = _p2;

    Point dp = p2 - p1;

    A = dp.getX();
    B = (-1) * dp.getY();
    C = p1.getX()*dp.getY() - p1.getY()*dp.getX();
}

double Line::getA() const {
    return A;
}

double Line::getB() const {
    return B;
}

double Line::getC() const {
    return C;
}

bool Line::operator||(const Line &rhs) const {
    double SCMult = std::abs(trunc(scalarMult(*this, rhs) * 1000)) / 1000;
    double lengthMult = trunc(length()*rhs.length() * 1000) / 1000;
    return std::abs(SCMult - lengthMult) < EPS;
}

double geometry::Line::length() const {
    return p1.getDistance(p2);
}

double geometry::scalarMult(const Line &line1, const Line &line2) {
    return line1.getA()*line2.getA() + line1.getB()*line2.getB();
}
