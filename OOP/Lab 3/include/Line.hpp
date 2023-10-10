#pragma once

#include "Point.hpp"
#include <stdexcept>

namespace geometry {
    class Line {
    private:
        Point p1;
        Point p2;
        double k;
        double b;
    public:
        Line(Point p1, Point p2);
        bool operator||(const Line & rhs) const;
        double length();
    };
};