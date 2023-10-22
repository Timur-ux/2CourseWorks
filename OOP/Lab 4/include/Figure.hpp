#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <algorithm>

#include "Point.hpp"
#include "Line.hpp"
#include "Validators.hpp"

class Figure {
protected:
	const std::string figureType;
	const int angles;

	Validator & validator;

	std::vector<Point> points;
	double square;
	Point geometryCenter;

	Figure(int _angles, std::string _figureType, Validator & _validator);

	virtual Point calcGeometryCenter(const std::vector<Point> & _points) const = 0;
	virtual double calcSquare(const std::vector<Point> & _points) const = 0;
public:
	virtual std::vector<Point> getPoints() const;
	virtual int getAngles() const;
	virtual std::string getFigureType() const;
	virtual Point getCenter() const;
	virtual operator double() const;

	virtual Figure & operator=(const Figure & rhs);
	virtual Figure & operator=(Figure && rhs);

	virtual bool operator==(const Figure & rhs) const;

	friend std::istream & operator>>(std::istream & is, Figure & figure);
};
std::ostream & operator<<(std::ostream & os, const Figure & figure);
std::istream & operator>>(std::istream & is, Figure & figure);
bool isParallel(const std::vector<Point> & points);

#include "Rectangle.hpp"
#include "Trapezoid.hpp"
#include "Romb.hpp"