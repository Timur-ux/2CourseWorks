#include "Figure.hpp"

std::vector<Point> Figure::getPoints() const {
    return points;
}

std::string Figure::getFigureType() const {
    return figureType;
}

int Figure::getAngles() const {
    return angles;
}

bool Figure::operator==(const Figure &rhs) const {
    return double(*this) == double(rhs);
}

bool Figure::operator<(const Figure &rhs) const {
    return double(*this) < double(rhs);
}

bool Figure::operator>(const Figure &rhs) const {
    return double(*this) > double(rhs);
}

std::ostream & operator<<(std::ostream & os, const Figure & figure) {
    os << figure.figureType << ": [ ";
    for(int i = 0; i < figure.points.size(); ++i) {
        os << figure.points[i] << ' ';
    }
    os << ']';
    
    return os;
}

std::istream & operator>>(std::istream & is, Figure & figure) {
    for(Point & point : figure.points) {
        is >> point;
    }

    return is;
}

