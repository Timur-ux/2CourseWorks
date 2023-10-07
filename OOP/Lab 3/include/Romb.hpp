#pragma once

#include "Figure.hpp"

namespace Figure {
    class Romb : public Figure {
    public:
        Romb(std::vector<Point> points);
        virtual Point getCenter() const override;
        virtual operator double() const override;
    };
}