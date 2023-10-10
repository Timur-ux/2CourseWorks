#pragma once

#include "Figure.hpp"

namespace geometry {

    class Romb : public Figure {
    private:
        virtual void assertPoints(const std::vector<Point> & _points) const override;
        virtual std::vector<Point> unificatePoints(std::vector<Point> _points) override;
        virtual Point calcGeometryCenter(const std::vector<Point> & _points) const override;
        virtual double calcSquare(const std::vector<Point> & _points) const override;
    public:
        Romb();
        Romb(std::vector<Point> & _points);
        Romb(std::vector<Point> && _points);
        Romb(const Romb & other);
        Romb(Romb && other) noexcept;

        virtual Figure & operator=(const Figure & rhs) override;
        virtual Figure & operator=(Figure && rhs) override;

        virtual bool operator==(const Figure & rhs) const override;
    };

};