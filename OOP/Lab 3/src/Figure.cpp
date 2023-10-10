#include "Figure.hpp"

using namespace geometry;

std::vector<Point> Figure::getPoints() const {
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

    figure.assertPoints(_points);
    figure.points = _points;
    figure.square = figure.calcSquare(_points);
    figure.geometryCenter = figure.calcGeometryCenter(_points);
    
    return is;
}
