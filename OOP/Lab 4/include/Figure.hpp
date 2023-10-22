#pragma once

#include <vector>
#include <string>
#include <cmath>

#include "Point.hpp"
#include "Line.hpp"

class Figure {
protected:
	const std::string figureType;
	const int angles;

	std::vector<Point> points;
	double square;
	Point geometryCenter;

	Figure(int _angles, std::string _figureType);

	virtual void Swap(const Figure & other);

	virtual Point calcGeometryCenter(const std::vector<Point> & _points) const = 0;
	virtual double calcSquare(const std::vector<Point> & _points) const = 0;
public:
	virtual std::vector<Point> getPoints() const;
	virtual int getAngles() const;
	virtual std::string getFigureType() const;
	virtual Point getCenter() const;
	virtual operator double() const;

	virtual Figure & operator=(const Figure & rhs) = 0;
	virtual Figure & operator=(Figure && rhs) noexcept = 0;

	virtual bool operator==(const Figure & rhs) const;

	friend std::istream & operator>>(std::istream & is, Figure & figure);
};

std::ostream & operator<<(std::ostream & os, const Figure & figure);