#include "1SinIntegral.hpp"


float SinIntegral(float A, float B, float e) {
	if (realizationType == ONE) {
		return __SinIntegralOne(A, B, e);
	}
	else if (realizationType == TWO) {
		return __SinIntegralTwo(A, B, e);
	}
}

float __SinIntegralOne(float A, float B, float e) {
	float result = 0;

	for (int i = A; i <= B; i += e) {
		result += sin(i) * e;
	}

	return result;
}

float __SinIntegralTwo(float A, float B, float e) {
	float result = 0;

	for (int i = A; i <= B; i += e) {
		result += (sin(i) + sin(i + e)) / 2 * e;
	}

	return result;
}
