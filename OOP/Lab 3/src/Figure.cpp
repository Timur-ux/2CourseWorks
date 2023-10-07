#include "Figure.hpp"

namespace Figure {
    Figure::Figure(int n) {
        points.assign(n, Point());
    }
    Point & Figure::operator[](int i)
    {
        return points.at(i);
    }

    std::ostream & operator<<(std::ostream & os, Figure & figure) {
        os << figure.figureType << ": [ ";
        for(Point & point : figure.points){
            os << point << ' ';
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
    
};
