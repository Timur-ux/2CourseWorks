#pragma once

#include "Point.hpp"
#include <stdexcept>

class Line {
private:
	Point p1;
	Point p2;
	double yKoef;
	double xKoef;
	double C;
public:
	Line(Point p1, Point p2);

	double getYKoef() const;
	double getXKoef() const;
	double getC() const;

	bool operator||(const Line & rhs) const;
	double length() const;
};

double scalarMult(const Line & line1, const Line & line2);
Point calcCross(const Line & line1, const Line & line2);
