#pragma once

#include "Validators.hpp"
#include "Figure.hpp"

#include <vector>
#include <typeinfo>
#include <memory>

namespace geometry {
	class FigureValidator {
	private:
		static std::vector <Validator *> validators;
	public:
		static void validate(const std::type_info & type, std::vector<Point> & _points);
	};

	std::vector<Validator *> FigureValidator::validators{
		new RectangleValidator(),
		new TrapezoidValidator(),
		new RombValidator()
	};
}