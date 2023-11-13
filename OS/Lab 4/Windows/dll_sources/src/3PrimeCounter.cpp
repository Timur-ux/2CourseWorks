#include "3PrimeCounter.hpp"

int PrimeCount(int A, int B) {
	if (realizationType == ONE) {
		return __PrimeCountOne(A, B);
	}
	else if (realizationType == TWO) {
		return __PrimeCountTwo(A, B);
	}

	throw std::logic_error("Bad realization type");
	return 0;
}

int __PrimeCountOne(int A, int B) {
	int result = 0;

	for (int i = A; i <= B; ++i) {
		bool isPrime = true;

		for (int k = 2; k * k < i; ++k) {
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

int __PrimeCountTwo(int A, int B) {
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
std::vector<bool> EratosthenesSieve::nums{ true, true };

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

		for (int j = prev; j < last; ++j) {
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
	return nums[n - 1];
}
