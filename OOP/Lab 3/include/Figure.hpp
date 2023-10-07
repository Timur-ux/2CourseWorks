#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <stdexcept>

#include "Point.hpp"

class Point;
class Figure {
protected:
    std::vector<Point> points;
    std::string figureType;
    int angles;
public:
    virtual std::vector<Point> getPoints() const;
    virtual std::string getFigureType() const;
    virtual int getAngles() const;
    
    virtual Point getCenter() const = 0;
    virtual operator double() const = 0;

    virtual Figure & operator=(const Figure & rhs) = 0;
    virtual Figure & operator=(Figure && rhs) = 0;

    virtual bool operator==(const Figure & rhs) const;
    virtual bool operator<(const Figure & rhs) const;
    virtual bool operator>(const Figure & rhs) const;

    friend std::ostream& operator<<(std::ostream& os, const Figure & figure);
    friend std::istream& operator>>(std::istream& is, Figure& figure);
};

std::ostream& operator<<(std::ostream& os, const Figure& figure);
std::istream& operator>>(std::istream& is, Figure& figure);

#include "Rectangle.hpp"
#include "Trapezoid.hpp"
#include "Romb.hpp"