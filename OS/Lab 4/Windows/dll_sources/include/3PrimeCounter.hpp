#ifndef PRIME_COUNTER_H_
#define PRIME_COUNTER_H_

#include "realizationType.hpp"
#include <vector>
#include <stdexcept>

__declspec(dllexport) int PrimeCount(int A, int B);

__declspec(dllexport) int __PrimeCountOne(int A, int B);

__declspec(dllexport) int __PrimeCountTwo(int A, int B);

class __declspec(dllexport) EratosthenesSieve {
private:
	static std::vector<bool> nums;
	static int last;
public:
	static void calcTo(int n);
	static bool isPrime(int n);
};

#endif