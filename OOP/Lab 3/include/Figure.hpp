#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <algorithm>

#include "Point.hpp"

namespace geometry {
    class Figure {
    protected:
        std::vector<Point> points;
        int angles;
        double square;
        Point geometryCenter;
        std::string figureType;

        virtual void assertPoints(std::vector<Point> & _points) const = 0;
        virtual std::vector<Point> unificatePoints(std::vector<Point> _points) = 0;
        virtual Point calcGeometryCenter(const std::vector<Point> & _points) const = 0;
        virtual double calcSquare(const std::vector<Point> & _points) const = 0;
    public:

        virtual std::vector<Point> getPoints() const;
        virtual int getAngles() const;
        virtual std::string getFigureType() const;
        virtual Point getCenter() const;
        virtual operator double() const;

        virtual Figure & operator=(const Figure & rhs) = 0;
        virtual Figure & operator=(Figure && rhs) = 0;

        virtual bool operator==(const Figure & rhs) const = 0;

        friend std::istream& operator>>(std::istream& is, Figure& figure);
    };
    std::ostream& operator<<(std::ostream& os, const Figure & figure);
    std::istream& operator>>(std::istream& is, Figure& figure);
};

#include "Rectangle.hpp"
#include "Trapezoid.hpp"
#include "Romb.hpp"