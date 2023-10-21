#pragma once

#include "Figure.hpp"
#include "FigureValidator.hpp"
#include <concepts>
#include <type_traits>

namespace geometry {

	template<class T>
		requires (std::is_base_of_v<Figure, T>)
	class FigureFabric {
	public:
		static T createInstance(std::vector<Point> _points);
	};

};