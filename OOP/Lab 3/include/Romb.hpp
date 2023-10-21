#pragma once

#include "Figure.hpp"

namespace geometry {

	class Romb : public Figure {
	private:
		virtual Point calcGeometryCenter(const std::vector<Point> & _points) const override;
		virtual double calcSquare(const std::vector<Point> & _points) const override;

		Romb(std::vector<Point> & _points);
		Romb(std::vector<Point> && _points);
	public:
		Romb();
		Romb(const Romb & other);
		Romb(Romb && other) noexcept;

		virtual Figure & operator=(const Figure & rhs);
		virtual Figure & operator=(Figure && rhs) noexcept;

		static Romb createInstance(std::vector<Point> _points) {
			_points = unificatePoints(_points);

			return Romb(_points);
		}
	};

};