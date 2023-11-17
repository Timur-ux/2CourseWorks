#include "lib2.hpp"

extern "C" float SinIntegral(float A, float B, float e) {
	float result = 0;

	for (float i = A; i <= B; i += e) {
		result += (sin(i) + sin(i + e)) / 2 * e;
	}

	return result;
}

extern "C" int PrimeCount(int A, int B) {
	EratosthenesSieve::calcTo(B);

	int result = 0;
	for (int i = A; i <= B; ++i) {
		if (EratosthenesSieve::isPrime(i)) {
			++result;
		}
	}

	return result;
}

// class EratosthenesSieve

int EratosthenesSieve::last = 2;
std::vector<bool> EratosthenesSieve::nums{ false, true };

void EratosthenesSieve::calcTo(int n) {
	if (n <= last) {
		return;
	}
	int prev = last;
	last = n;

	for (int i = prev; i < last; ++i) {
		nums.emplace_back(true);
	}

	for (int i = 1; i * i < last; ++i) {
		int curDeliter = i + 1;

		for (int j = curDeliter; j < last; ++j) {
			int curNum = j + 1;

			if (curNum % curDeliter == 0) {
				for (int k = j; k < last; k += curDeliter) {
					nums[k] = false;
				}
				break;
			}
		}
	}
}

bool EratosthenesSieve::isPrime(int n) {
	if (n < 1) {
		return false;
	}
	return nums[n - 1];
}
