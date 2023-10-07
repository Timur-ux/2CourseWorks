#pragma once

#include "Figure.hpp"
#include "Point.hpp"


class Rectangle : public Figure {
public:
    Rectangle(std::vector<Point> & _points);
    Rectangle(std::vector<Point> && _points);

    virtual Point getCenter() const override;
    virtual operator double() const override;

    virtual Figure & operator=(const Figure &rhs) override;
    virtual Figure & operator=(Figure && rhs) override;

    virtual bool operator==(const Figure & rhs) const;
};