#include "1SinIntegral.hpp"
#include <iostream>

extern "C" float SinIntegral(float A, float B, float e) {
	if (realizationType == 0) {
		return __SinIntegralOne(A, B, e);
	}
	else if (realizationType == 1) {
		return __SinIntegralTwo(A, B, e);
	}

	throw std::logic_error("Invalid realization type");
	return 0;
}

float __SinIntegralOne(float A, float B, float e) {
	float result = 0;

	for (float i = A; i <= B; i += e) {
		result += sin(i) * e;
	}

	return result;
}

float __SinIntegralTwo(float A, float B, float e) {
	float result = 0;

	for (float i = A; i <= B; i += e) {
		result += (sin(i) + sin(i + e)) / 2 * e;
	}

	return result;
}

extern "C" int SinRealizationChange() {
	realizationType = (realizationType + 1) % 2;
	return realizationType;
};