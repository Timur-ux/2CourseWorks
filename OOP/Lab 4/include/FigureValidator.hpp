#ifndef FIGURE_VALIDATOR_H_
#define FIGURE_VALIDATOR_H_

#include "Validators.hpp"
#include "Figure.hpp"

#include <vector>
#include <typeinfo>
#include <memory>

namespace {
	class FigureValidator {
	private:
		static std::vector <std::shared_ptr<Validator>> validators;
	public:
		static void validate(const std::type_info & type, std::vector<Point> & _points);
	};

	std::vector <std::shared_ptr<Validator>> FigureValidator::validators{
		std::shared_ptr<Validator>{new RectangleValidator},
		std::shared_ptr<Validator>{new TrapezoidValidator},
		std::shared_ptr<Validator>{new RombValidator}
	};

	void FigureValidator::validate(const std::type_info & type, std::vector<Point> & _points) {
		bool isTypeRecognized = false;

		for (auto validator : validators) {
			if (validator->isAllowedFor(type)) {
				isTypeRecognized = true;
				validator->validate(_points);
			}
		}

		if (not isTypeRecognized) {
			std::string error = "Undefined type ";
			throw std::invalid_argument(error + type.name());
		}
	}
}
#endif