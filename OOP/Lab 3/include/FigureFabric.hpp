#ifndef FIGURE_FABRIC_H_
#define FIGURE_FABRIC_H_

#include "Figure.hpp"
#include "FigureValidator.hpp"
#include <concepts>
#include <type_traits>

namespace geometry {
	template<class T>
		requires std::is_base_of_v<Figure, T>
	class FigureFabric {
	public:
		static T * createInstance(std::vector<Point> _points);
	};

	template<class T> requires std::is_base_of_v<Figure, T>
	inline T * FigureFabric<T>::createInstance(std::vector<Point> _points) {
		_points = unificatePoints(_points);
		FigureValidator::validate(typeid(T), _points);
		return new T(_points);
	}
}

#endif