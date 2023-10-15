#pragma once

#include "Figure.hpp"

namespace geometry {

    class Romb : public Figure {
    private:
        virtual Point calcGeometryCenter(const std::vector<Point> & _points) const override;
        virtual double calcSquare(const std::vector<Point> & _points) const override;
    public:
        Romb();
        Romb(std::vector<Point> & _points);
        Romb(std::vector<Point> && _points);
        Romb(const Romb & other);
        Romb(Romb && other) noexcept;
    };

};