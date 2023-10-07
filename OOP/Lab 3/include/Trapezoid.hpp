#pragma once

#include "Figure.hpp"

class Trapezoid : public Figure {
private:
    void setBaseParameters();
public:
    Trapezoid(std::vector<Point> & _points);
    Trapezoid(std::vector<Point> && _points);
    Trapezoid(const Trapezoid & other);
    Trapezoid(Trapezoid && other) noexcept;

    virtual Point getCenter() const override;
    virtual operator double() const override;

    virtual Figure & operator=(const Figure & rhs) override;
    virtual Figure & operator=(Figure && rhs) override;
};
