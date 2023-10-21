#pragma once

#include "Figure.hpp"
#include "Point.hpp"

class Rectangle : public Figure {
private:
	virtual Point calcGeometryCenter(const std::vector<Point> & _points) const override;
	virtual double calcSquare(const std::vector<Point> & _points) const override;
public:
	Rectangle();
	Rectangle(std::vector<Point> & _points);
	Rectangle(std::vector<Point> && _points);
	Rectangle(const Rectangle & other);
	Rectangle(Rectangle && other) noexcept;
};