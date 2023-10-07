#pragma once

#include "Figure.hpp"
#include "FigureBuilder.hpp"


namespace Figure {
    class FigureFabric {
    public:
        Figure * produceFigure(FigureBuilder * builder, std::vector<Point> &_points);
    };
};