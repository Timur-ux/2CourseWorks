#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <algorithm>

#include "Point.hpp"
#include "Line.hpp"

namespace geometry {
    class Figure {
    protected:
        const std::string figureType;
        const int angles;
        std::vector<Point> points;
        double square;
        Point geometryCenter;

        Figure(int _angles, std::string _figureType);
        virtual void assertPoints(const std::vector<Point> & _points) const = 0;
        virtual std::vector<Point> unificatePoints(std::vector<Point> _points);

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
    bool isParallel(const std::vector<Point>& points);
};

#include "Rectangle.hpp"
#include "Trapezoid.hpp"
#include "Romb.hpp"