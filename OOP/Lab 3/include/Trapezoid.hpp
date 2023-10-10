#pragma once

#include "Figure.hpp"

namespace geometry {

    class Trapezoid : public Figure {
    private:
        virtual void assertPoints(const std::vector<Point> & _points) const override;
        virtual Point calcGeometryCenter(const std::vector<Point> & _points) const override;
        virtual double calcSquare(const std::vector<Point> & _points) const override;
    public:
        Trapezoid();
        Trapezoid(std::vector<Point> & _points);
        Trapezoid(std::vector<Point> && _points);
        Trapezoid(const Trapezoid & other);
        Trapezoid(Trapezoid && other) noexcept;

        virtual Figure & operator=(const Figure & rhs) override;
        virtual Figure & operator=(Figure && rhs) override;

        virtual bool operator==(const Figure & rhs) const override;
    };
}
