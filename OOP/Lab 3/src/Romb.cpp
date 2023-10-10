#include "Romb.hpp"

using namespace geometry;

void Romb::assertPoints(std::vector<Point> & _points) const {
    Line line1(_points[0], _point[1]);
    Line line2(_points[1], _point[2]);
    Line line3(_points[2], _points[3]);
    Line line4(_points[3], _points[0]);
    if(not((line1 || line3) and (line2 || line4))) {
        throw new std::invalid_argument("Incrrect points for Romb");
    }
}

std::vector<Point> geometry::Romb::unificatePoints(std::vector<Point> _points) {
    if(_points.size() != angles) {
        throw new std::invalid_argument("Incrrect points for Romb");
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

Romb::Romb() {
    angles = 4;
    square = 0;
    geometryCenter = Point(0, 0);
    figureType = "Romb";
}

Romb::Romb(std::vector<Point> & _points) : Romb() {
    points = unificatePoints(_points);
    assertPoints(_points);
    
    geometryCenter = calcGeometryCenter(_points);
    square = calcSquare(_points);
}

Romb::Romb(std::vector<Point> && _points) : Romb() {
    points = unificatePoints(_points);
    assertPoints(points);
    
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
    assertPoints(points);

    geometryCenter = rhs.getCenter();
    square = double(rhs);

    return *this;
}

Figure &Romb::operator=(Figure &&rhs) {
    points = unificatePoints(rhs.getPoints());
    assertPoints(points);
    
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