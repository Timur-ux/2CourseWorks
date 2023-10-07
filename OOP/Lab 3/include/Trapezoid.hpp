#pragma once

#include "Figure.hpp"

class Trapezoid : public Figure {
public:
    Trapezoid();
    Trapezoid(std::vector<Point> points);
    virtual Point getCenter() const override;
    virtual operator double() const override;
};
