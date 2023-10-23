#include "Point.hpp"

using namespace geometry;

Point::Point(decart cord) : x(cord.first),
                            y(cord.second) {}

Point::Point(const Point &other) : x(other.x),
                                    y(other.y) {}

Point::Point(Point &&other) noexcept {
    x = other.x;
    y = other.y;

    other.x = 0;
    other.y = 0;
}

decart Point::getDecart() const {
    return decart(x, y);
}

double Point::getX() const {
    return x;
}

double Point::getY() const {
    return y;
}

double Point::getDistance(const Point &other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    return sqrt(dx*dx + dy*dy);
}

Point Point::operator+(const Point &rhs) const {
    double x1 = x + rhs.x;
    double y1 = y + rhs.y;
    return Point(decart(x1, y1));
}
Point Point::operator-(const Point &rhs) const {
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
    return (std::abs(x - rhs.x) < EPS and std::abs(y - rhs.y) < EPS);
}

bool geometry::cmpX(const Point & lhs, const Point & rhs) {
    return lhs.getX() < rhs.getX();
}

bool geometry::cmpY(const Point &lhs, const Point &rhs)  {
    return lhs.getY() < rhs.getY();
}

Point geometry::operator*(int k, const Point &point)
{
    return Point(decart(k*point.x, k*point.y));
}

Point geometry::operator*(const Point &point, int k) {
    return k * point;
}

Point geometry::operator/(const Point &point, int k) {
    return Point(decart(point.x / k, point.y / k));
}
Point geometry::abs(const Point &point) {
    Point result;
    result.x = (point.x < 0) ? (-1)*point.x : point.x;
    result.y = (point.y < 0) ? (-1)*point.y : point.y;
    
    return result; 
}
std::ostream & geometry::operator<<(std::ostream &os, const geometry::Point &point) {
    os << "{" << point.getX() << ' ' << point.getY() << "}";
    
    return os;
}

std::istream &geometry::operator>>(std::istream &is, Point &point) {
    is >> point.x >> point.y;
    
    return is;
}

Point sum(const std::vector<Point> & _points);

std::vector<Point> geometry::unificatePoints(std::vector<Point> _points) {
    // setting points in clock otherwise order
    std::vector<Point> result;
    
    Point centralPoint = sum(_points) / _points.size();
    std::vector<Point> aboveCentralPoints;

    std::sort(_points.begin(), _points.end(), cmpX);

    for(auto it = _points.begin(); it != _points.end(); ++it) {
        if((*it).getY() <= centralPoint.getY()) {
            result.push_back(*it);
        } else {
            aboveCentralPoints.push_back(*it);
        }
    }
    
    std::reverse(aboveCentralPoints.begin(), aboveCentralPoints.end());
    
    for(auto it = aboveCentralPoints.begin(); it != aboveCentralPoints.end(); ++it) {
        result.push_back(*it);
    }

    return result;
}

Point sum(const std::vector<Point> &_points) {
    Point result;
    
    for(Point point : _points) {
        result = result + point;
    }

    return result;
}