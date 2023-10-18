#include "Line.hpp"

using namespace geometry;

Line::Line(Point _p1, Point _p2) {
    if(_p1 == _p2) {
        throw std::invalid_argument("Line need 2 not equal point, equals given");
    }

    p1 = _p1;
    p2 = _p2;

    Point dp = p2 - p1;

    yKoef = dp.getX();
    xKoef = (-1) * dp.getY();
    C = p1.getX()*dp.getY() - p1.getY()*dp.getX();
}

double Line::getYKoef() const {
    return yKoef;
}

double Line::getXKoef() const {
    return xKoef;
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
    return line1.getYKoef()*line2.getYKoef() + line1.getXKoef()*line2.getXKoef();
}

Point geometry::calcCross(const Line &line1, const Line &line2) {
    if(line1 || line2) {
        throw std::logic_error("Parallel lines are uncrossable");
    }

    double crossX = (line2.getYKoef()*line1.getC() - line1.getYKoef()*line2.getC())
                / (line2.getXKoef()*line1.getYKoef() - line1.getXKoef()*line2.getYKoef());
    double crossY = -(line1.getC() + line1.getXKoef()*crossX) / line1.getYKoef();

    return Point(crossX, crossY);
}
