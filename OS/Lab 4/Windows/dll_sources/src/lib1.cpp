#include "lib1.hpp"

extern "C" float SinIntegral(float A, float B, float e) {
	float result = 0;

	for (float i = A; i <= B; i += e) {
		result += sin(i) * e;
	}

	return result;
}


extern "C" int PrimeCount(int A, int B) {
	int result = 0;

	for (int i = max(A, 2); i <= B; ++i) {
		bool isPrime = true;

		for (int k = 2; k < i; ++k) {
			if (i % k == 0) {
				isPrime = false;
				break;
			}
		}

		if (isPrime) {
			++result;
		}
	}
	return result;
}