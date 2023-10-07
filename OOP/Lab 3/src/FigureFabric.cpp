#include "FigureFabric.hpp"

namespace Figure {
    Figure *FigureFabric::produceFigure(FigureBuilder *builder, std::vector<Point> & _points) {
        builder ->setPoints(_points);
        return builder->getFigure();
    }
}