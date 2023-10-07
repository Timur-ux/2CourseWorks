#pragma once

#include "Point.hpp"
#include "Rectangle.hpp"
#include "Trapezoid.hpp"
#include "Romb.hpp"

#include <vector>
#include <iostream>
#include <cmath>

namespace Figure
{
    class Figure {
    private:
        std::vector<Point> points;
    protected:
        std::string figureType;
    public:
        Figure() = delete;
        Figure(int n);
        Figure(std::vector<Point> _points) : points(_points) {};

        virtual Point getCenter() const = 0;
        virtual operator double() const = 0;
        
        friend std::ostream& operator<<(std::ostream& os, Figure & figure);
        friend std::istream& operator>>(std::istream& is, Figure& figure);

        Point & operator[](int i);
    };
    
    std::ostream& operator<<(std::ostream& os, const Figure& figure);
    std::istream& operator>>(std::istream& is, Figure& figure);
};
