#ifndef FIGURE_VALIDATOR_H_
#define FIGURE_VALIDATOR_H_

#include "Validators.hpp"
#include "Figure.hpp"

#include <vector>
#include <typeinfo>
#include <memory>

namespace geometry {
	namespace {
		class FigureValidator {
		private:
			static std::vector <Validator *> validators;
		public:
			static void validate(const std::type_info & type, std::vector<Point> & _points);
		};

		std::vector <Validator *> FigureValidator::validators = {
			new RectangleValidator,
			new TrapezoidValidator,
			new RombValidator
		};

		void FigureValidator::validate(const std::type_info & type, std::vector<Point> & _points) {
			bool isTypeRecognized = false;

			for (int i = 0; i < validators.size(); ++i) {
				auto validator = validators[i];

				if (validator->isAllowedFor(type)) {
					isTypeRecognized = true;
					validator->validate(_points);
				}
			}

			if (not isTypeRecognized) {
				throw std::invalid_argument("Undefined type");
			}
		}
	}
}
#endif