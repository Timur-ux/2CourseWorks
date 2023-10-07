#include "Point.hpp"

Point::Point(decart cord) : x(cord.first),
                            y(cord.second) {}

Point::Point(const Point &other) : x(other.x),
                                    y(other.y) {}

Point::Point(Point &&other) {
    x = other.x;
    y = other.y;

    other.x = 0;
    other.y = 0;
}

decart Point::getDecart() const {
    return decart(x, y);
}

double Point::getDistance(Point &other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    return sqrt(dx*dx + dy*dy);
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

Point &Point::operator=(const Point &rhs) {
    x = rhs.x;
    y = rhs.y;

    return *this;
}

Point &Point::operator=(Point &&rhs) {
    x = rhs.x;
    y = rhs.y;

    rhs.x = 0;
    rhs.y = 0;
    
    return *this;
}

bool Point::operator==(const Point &rhs) const
{
    return (x == rhs.x and y == rhs.y);
}

Point operator*(int k, const Point &point) {
    return Point(decart(k*point.x, k*point.y));
}

Point operator*(const Point &point, int k) {
    return k * point;
}

Point operator/(const Point &point, int k) {
    return Point(decart(point.x / k, point.y / k));
}
Point abs(const Point &point) {
    Point result;
    result.x = (point.x < 0) ? (-1)*point.x : point.x;
    result.y = (point.y < 0) ? (-1)*point.y : point.y;
    
    return result; 
}
std::ostream &operator<<(std::ostream &os, const Point &point)
{
    os << "{" << point.x << ' ' << point.y << "}";
    
    return os;
}
std::istream &operator>>(std::istream &is, Point &point) {
    is >> point.x >> point.y;
    
    return is;
}
