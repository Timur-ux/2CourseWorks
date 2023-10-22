#pragma once

#include "Figure.hpp"

class Trapezoid : public Figure {
private:
	virtual Point calcGeometryCenter(const std::vector<Point> & _points) const override;
	virtual double calcSquare(const std::vector<Point> & _points) const override;

public:
	Trapezoid();
	Trapezoid(std::vector<Point> & _points);
	Trapezoid(std::vector<Point> && _points);
	Trapezoid(const Trapezoid & other);
	Trapezoid(Trapezoid && other) noexcept;

	virtual Figure & operator=(const Figure & rhs);
	virtual Figure & operator=(Figure && rhs) noexcept;

};
