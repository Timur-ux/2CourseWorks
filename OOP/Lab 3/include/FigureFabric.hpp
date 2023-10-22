#ifndef FIGURE_FABRIC_H_
#define FIGURE_FABRIC_H_

#include "Figure.hpp"
#include "Rectangle.hpp"
#include "Trapezoid.hpp"
#include "Romb.hpp"

#include "FigureValidator.hpp"
#include <concepts>
#include <type_traits>

namespace geometry {
	template<class T>
		requires std::is_base_of_v<Figure, T>
	class FigureFabric {
	public:
		static T * createInstance(std::vector<Point> _points);
		static T * createInstance();
	};

	template<class T> requires std::is_base_of_v<Figure, T>
	inline T * FigureFabric<T>::createInstance(std::vector<Point> _points) {
		_points = unificatePoints(_points);
		FigureValidator::validate(typeid(T), _points);
		return new T(_points);
	}

	template<class T> requires std::is_base_of_v<Figure, T>
	inline T * FigureFabric<T>::createInstance() {
		return new T;
	}

	inline std::istream & operator>>(std::istream & is, Figure & figure) {
		std::vector<Point> _points(figure.getAngles());
		for (Point & point : _points) {
			is >> point;
		}

		_points = unificatePoints(_points);
		FigureValidator::validate(typeid(figure), _points);

		figure.points = _points;
		figure.square = figure.calcSquare(figure.points);
		figure.geometryCenter = figure.calcGeometryCenter(figure.points);

		return is;
	}
}
#endif