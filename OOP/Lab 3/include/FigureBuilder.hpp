#pragma once

#include "Figure.hpp"

namespace Figure {
    class FigureBuilder {
    public:
        virtual FigureBuilder * setPoints(std::vector<Point> & _points) = 0;

        virtual Figure * getFigure() = 0;
    };
};