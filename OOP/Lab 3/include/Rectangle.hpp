#pragma once

#include "Figure.hpp"
#include "Point.hpp"

namespace geometry {

    class Rectangle : public Figure {
    private:
        virtual void assertPoints(std::vector<Point> & _points) const override;
        virtual std::vector<Point> unificatePoints(std::vector<Point> _points) override;
        virtual Point calcGeometryCenter(const std::vector<Point> & _points) const override;
        virtual double calcSquare(const std::vector<Point> & _points) const override;
    public:
        Rectangle();
        Rectangle(std::vector<Point> & _points);
        Rectangle(std::vector<Point> && _points);
        Rectangle(const Rectangle & other);
        Rectangle(Rectangle && other) noexcept;

        virtual Figure & operator=(const Figure &rhs) override;
        virtual Figure & operator=(Figure && rhs) override;

        virtual bool operator==(const Figure & rhs) const override;
    };

};