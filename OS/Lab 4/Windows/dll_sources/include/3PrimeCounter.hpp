#ifndef PRIME_COUNTER_H_
#define PRIME_COUNTER_H_

#include "realizationType.hpp"
#include <vector>
#include <stdexcept>

int PrimeCount(int A, int B);

int __PrimeCountOne(int A, int B);

int __PrimeCountTwo(int A, int B);

class EratosthenesSieve {
private:
	static std::vector<bool> nums;
	static int last;
public:
	static void calcTo(int n);
	static bool isPrime(int n);
};

#endif