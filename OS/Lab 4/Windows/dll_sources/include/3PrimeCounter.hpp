#ifndef PRIME_COUNTER_H_
#define PRIME_COUNTER_H_
#include <vector>
#include <stdexcept>

static int realizationType = 0;

extern "C" __declspec(dllexport) int __cdecl PrimesRealizationChange();

extern "C" __declspec(dllexport) int __cdecl PrimeCount(int A, int B);

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