#pragma once

#include "FigureBuilder.hpp"
#include "Point.hpp"
#include "Rectangle.hpp"
#include "Trapezoid.hpp"
#include "Romb.hpp"

#include <vector>
#include <iostream>
#include <cmath>
#include <stdexcept>

namespace Figure
{
    class Figure {
    protected:
        std::vector<Point> points;
        std::string figureType;
        int angles;
    public:
        friend class FigureBuilder;

        Figure() = default;

        virtual void setPoints(std::vector<Point> & _points) = 0;

        std::vector<Point> getPoints() const;
        virtual Point getCenter() const = 0;
        virtual operator double() const = 0;

        virtual Figure & operator=(const Figure & rhs) = 0;
        virtual Figure & operator=(Figure && rhs) = 0;

        virtual bool operator==(const Figure & rhs) const = 0;

        friend std::ostream& operator<<(std::ostream& os, const Figure & figure);
        friend std::istream& operator>>(std::istream& is, Figure& figure);
    };
    
    std::ostream& operator<<(std::ostream& os, const Figure& figure);
    std::istream& operator>>(std::istream& is, Figure& figure);
};
