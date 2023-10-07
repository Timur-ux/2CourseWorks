#pragma once

#include "Figure.hpp"

namespace Figure {
    class Rectangle : public Figure {
    public:
        Rectangle();
        Rectangle(std::vector<Point> points);
        virtual Point getCenter() const override;
        virtual operator double() const override;
    };
}