#include "Figure.hpp"

using namespace geometry;



Figure::Figure(int _angles, std::string _figureType, Validator & _validator)
 : angles(_angles)
, figureType(_figureType)
, validator(_validator)
, square(0)
, geometryCenter(0, 0) {}

std::vector<Point> Figure::getPoints() const
{
    return points;
}

int Figure::getAngles() const {
    return angles;
}

std::string geometry::Figure::getFigureType() const {
    return figureType;
}

Point Figure::getCenter() const {
    return geometryCenter;
}

geometry::Figure::operator double() const {
    return square;
}

Figure &geometry::Figure::operator=(const Figure &rhs) {
    std::vector<Point> rhsPoints = rhs.getPoints();
    points = unificatePoints(rhsPoints);

    validator.validate(points);
    
    geometryCenter = rhs.getCenter();
    square = double(rhs);
    
    delete &rhs;
    return *this;
}

Figure &geometry::Figure::operator=(Figure &&rhs) {
    std::vector<Point> rhsPoints = rhs.getPoints();
    points = unificatePoints(rhsPoints);
    
    validator.validate(points);

    geometryCenter = rhs.getCenter();
    square = double(rhs);

    return *this;
}

bool geometry::Figure::operator==(const Figure &rhs) const {
    std::vector<Point> rhsPoints = rhs.getPoints();
    validator.validate(rhsPoints);
    return double(*this) == double(rhs);
}

std::ostream & geometry::operator<<(std::ostream & os, const Figure & figure) {
    std::vector<Point> points = figure.getPoints();
    
    os << figure.getFigureType() << ": [ ";
    for(Point point : figure.getPoints()) {
        os << point << ' ';
    }
    os << ']' << std::endl;
    os << "Geometry center = " << figure.getCenter() << std::endl; 
    os << "Square = " << double(figure) << std::endl;

    return os;
}

std::istream & geometry::operator>>(std::istream &is, Figure &figure) {
    std::vector<Point> _points(figure.getAngles());
    for(Point & point : _points) {
        is >> point;
    }

    figure.points = unificatePoints(_points);
    figure.square = figure.calcSquare(figure.points);
    figure.geometryCenter = figure.calcGeometryCenter(figure.points);
    
    return is;
}

bool geometry::isParallel(const std::vector<Point> &points){
    if(points.size() != 4) {
        throw std::invalid_argument("isParallel need 4 points exactly");
    }

    Point line1 = (points[1] - points[0]);
    double k1 = line1.getX() == 0 ? 0 : line1.getY() / line1.getX();
    
    Point line2 = (points[3] - points[2]);
    double k2 = line2.getX() == 0 ? 0 : line2.getY() / line2.getX();

    return k1 == k2;
}