#pragma once

#include <cmath>
#include <vector>
#ifdef LIB2_EXPORTS
#define LIB2_API __declspec(dllexport)
#else
#define LIB2_API __declspec(dllimport)
#endif

extern "C" LIB2_API float SinIntegral(float A, float B, float e);

extern "C" LIB2_API int PrimeCount(int A, int B);

class EratosthenesSieve {
private:
	static std::vector<bool> nums;
	static int last;
public:
	static void calcTo(int n);
	static bool isPrime(int n);
};