#include "Point.hpp"

namespace Figure {
    Point::Point(decart cord) : x(cord.first),
                                y(cord.second) {}
    Point::Point(polar cord) {
        x = cord.first*cos(cord.second);
        y = cord.first*sin(cord.second);
    }

    Point::Point(const Point &other) : x(other.x),
                                        y(other.y) {}

    decart Point::getDecart() const {
        return decart(x, y);
    }

    polar Point::getPolar() const {
        double r = sqrt(x*x + y*y);
        double theta = asin(y / r);
        return polar(r, theta);
    }

    double Point::getDistance(Point &other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return sqrt(dx*dx + dy*dy);;
    }

    Point Point::operator+(const Point &rhs) const {
        double x1 = x + rhs.x;
        double y1 = y + rhs.y;
        return Point(decart(x1, y1));
    }
    Point Point::operator-(const Point &rhs) const
    {
        double x1 = x - rhs.x;
        double y1 = y - rhs.y;
        return Point(decart(x1, y1));
    }

    Point operator*(int k, Point &point) {
        return Point(decart(k*point.x, k*point.y));
    }

    Point operator*(Point &point, int k) {
        return k * point;
    }

    Point operator/(Point &point, int k) {
        return Point(decart(point.x / k, point.y / k));
    }
    std::ostream &operator<<(std::ostream &os, Point &point) {
        // TODO: вставьте здесь оператор return
    }
}