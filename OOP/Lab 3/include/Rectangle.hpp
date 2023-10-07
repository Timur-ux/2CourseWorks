#pragma once

#include "Figure.hpp"
#include "Point.hpp"


class Rectangle : public Figure {
private:
    void setBaseParameters();
public:
    Rectangle(std::vector<Point> & _points);
    Rectangle(std::vector<Point> && _points);
    Rectangle(const Rectangle & other);
    Rectangle(Rectangle && other) noexcept;

    virtual Point getCenter() const override;
    virtual operator double() const override;

    virtual Figure & operator=(const Figure &rhs) override;
    virtual Figure & operator=(Figure && rhs) override;
};