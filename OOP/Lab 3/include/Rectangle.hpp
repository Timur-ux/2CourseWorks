#pragma once

#include "Figure.hpp"
#include "Point.hpp"

namespace geometry {

	class Rectangle : public Figure {
	private:
		virtual Point calcGeometryCenter(const std::vector<Point> & _points) const override;
		virtual double calcSquare(const std::vector<Point> & _points) const override;

		Rectangle(std::vector<Point> & _points);
		Rectangle(std::vector<Point> && _points);
	public:
		Rectangle();
		Rectangle(const Rectangle & other);
		Rectangle(Rectangle && other) noexcept;

		virtual Figure & operator=(const Figure & rhs);
		virtual Figure & operator=(Figure && rhs) noexcept;

		static Rectangle createInstance(std::vector<Point> _points) {
			_points = unificatePoints(_points);
			return Rectangle(_points);
		}
	};
};