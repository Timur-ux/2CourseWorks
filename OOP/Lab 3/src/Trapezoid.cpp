#include "Trapezoid.hpp"

using namespace geometry;

void Trapezoid::assertPoints(std::vector<Point> & _points) const {
    if(_points.size() != angles) {
        throw new std::invalid_argument("Incorrect points for Trapezoid");
    }

    Line line1(_points[0], _points[1]);
    Line line2(_points[2], _points[3]);
    if(not (line1 || line2)) {
        throw new std::invalid_argument("Incorrect points for Trapezoid");
    }
}

std::vector<Point> Trapezoid::unificatePoints(std::vector<Point> _points) {
    if(_points.size() != angles) {
        throw new std::invalid_argument("Incorrect points for Trapezoid");
    }

    std::vector<Point> result;
    std::vector<Point> temp;

    std::sort(_points.begin(), _points.end(), cmpX);

    Point centralPoint = (_points[0] + _points[1] + _points[2] + _points[3]) / 4;
    for(auto it = _points.begin(); it != _points.end(); ++it) {
        if(it->getY() <= centralPoint.getY()) {
            result.push_back(*it);
        } else {
            temp.push_back(*it);
        }
    }
    
    std::stable_sort(temp.begin(), temp.end(), [](const Point & lhs, const Point & rhs) {
        return not cmpX(lhs, rhs);
    });
    
    for(auto it = temp.begin(); it != temp.end(); ++it) {
        result.push_back(*it);
    }

    return result;
}

Trapezoid::Trapezoid() {
    angles = 4;
    square = 0;
    geometryCenter = Point(0, 0);
    figureType = "Trapezoid";
}

Trapezoid::Trapezoid(std::vector<Point> &_points) : Trapezoid() {
    points = unificatePoints(_points);
    assertPoints(points);

    geometryCenter = calcGeometryCenter(_points);
    square = calcSquare(_points);
}

Trapezoid::Trapezoid(std::vector<Point> &&_points) : Trapezoid() {
    points = unificatePoints(_points);
    assertPoints(points);

    geometryCenter = calcGeometryCenter(_points);
    square = calcSquare(_points);
}

Trapezoid::Trapezoid(const Trapezoid &other) : Trapezoid() {
    points = other.getPoints();
    geometryCenter = other.getCenter();
    square = double(other);
}

Trapezoid::Trapezoid(Trapezoid && other) noexcept : Trapezoid() {
    points = other.getPoints();
    geometryCenter = other.getCenter();
    square = double(other);
    
    delete &other;
}

Point Trapezoid::calcGeometryCenter(const std::vector<Point> & _points) const {
    Point diff13 = _points[2] - _points[0];
    double k1 = diff13.getY() / diff13.getX();

    Point diff24 =  _points[3] - _points[1];
    double k2 = diff24.getY() / diff24.getX();

    double b1 = _points[0].getY() - _points[0].getX() * k1;
    double b2 = _points[1].getY() - _points[1].getX() * k2;

    double crossX = (b1 - b2) / (k2 - k1);
    double crossY = k1 * crossX + b1;

    return Point(decart(crossX, crossY));
}

double Trapezoid::calcSquare(const std::vector<Point> & _points) const {
    double a = _points[0].getDistance(_points[1]);
    double b = _points[2].getDistance(_points[3]);
    double h = abs(_points[0] - _points[2]).getY();

    return (a + b) * h / 2; 
}

Figure &Trapezoid::operator=(const Figure &rhs) {
    points = unificatePoints(rhs.getPoints());
    assertPoints(points);
    
    square = double(rhs);
    geometryCenter = rhs.getCenter();

    return *this; 
}

Figure &Trapezoid::operator=(Figure &&rhs) {
    points = unificatePoints(rhs.getPoints());
    assertPoints(points);
    
    square = double(rhs);
    geometryCenter = rhs.getCenter();
    
    delete &rhs;
    return *this;
}

bool Trapezoid::operator==(const Figure &rhs) const {
    std::vector<Point> rhsPoints = rhs.getPoints();
    assertPoints(rhsPoints);

    return double(*this) == double(rhs);
}