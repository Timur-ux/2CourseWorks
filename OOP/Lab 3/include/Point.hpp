#pragma once

#include "Figure.hpp"

#include <iostream>
#include <cmath>

namespace Figure {
    
    using decart = std::pair<double, double>;
    using polar = std::pair<double, double>;

    class Point {
    private:
        double x;
        double y;
    public:
        Point() = default;
        Point(const decart cordinate);
        Point(const polar cordinate);
        Point(const Point & other);
        Point(Point && other);

        ~Point() = default;

        decart getDecart() const;
        polar getPolar() const;
        
        double getDistance(Point & other) const;
        
        Point operator+(const Point & rhs) const;
        Point operator-(const Point & rhs) const;

        Point & operator=(const Point & rhs);
        Point & operator=(Point && rhs);

        bool operator==(const Point & rhs) const;

        friend Point operator*(int k, const Point & point);
        friend Point operator*(const Point & point, int k);
        friend Point operator/(const Point & point, int k);
        friend Point & abs(Point && point);

        friend std::ostream& operator<<(std::ostream& os, const Point& point);
        friend std::istream& operator>>(std::istream& is, Point& point);
    };
    
    Point operator*(int k, const Point & point);
    Point operator*(const Point & point, int k);
    Point operator/(const Point & point, int k);
    Point & abs(Point && point);
    
    std::ostream& operator<<(std::ostream& os, const Point& point);
    std::istream& operator>>(std::istream& is, Point& point);    
};
