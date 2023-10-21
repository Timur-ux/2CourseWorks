#include "FigureValidator.hpp"

using namespace geometry;

void FigureValidator::validate(const std::type_info & type, std::vector<Point> & _points) {
	bool isTypeRecognized = false;

	for (Validator *& validator : validators) {
		if (validator->isAllowedFor(type)) {
			isTypeRecognized = true;
			validator->validate(_points);
		}
	}

	if (not isTypeRecognized) {
		throw std::invalid_argument("Undefined type");
	}
}