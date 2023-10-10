#pragma once

#include "Point.hpp"
#include <stdexcept>

namespace geometry {
    class Line {
    private:
        Point p1;
        Point p2;
        double A;
        double B;
        double C;
    public:
        Line(Point p1, Point p2);
        
        double getA() const;
        double getB() const;
        double getC() const;

        bool operator||(const Line & rhs) const;
        double length() const;

    };

    double scalarMult(const Line & line1, const Line & line2);
};