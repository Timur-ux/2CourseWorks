#pragma once

#include "Figure.hpp"

class Romb : public Figure {
private:
    void setBaseParameters();
public:
    Romb(std::vector<Point> & _points);
    Romb(std::vector<Point> && _points);
    Romb(const Romb & other);
    Romb(Romb && other) noexcept;

    virtual Point getCenter() const override;
    virtual operator double() const override;

    virtual Figure & operator=(const Figure & rhs) override;
    virtual Figure & operator=(Figure && rhs) override;
};

