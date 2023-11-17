#pragma once

#include <cmath>

#define max(A, B) (A > B ? A : B)

#ifdef LIB1_EXPORTS
#define LIB1_API __declspec(dllexport)
#else
#define LIB1_API __declspec(dllimport)
#endif

extern "C" LIB1_API float SinIntegral(float A, float B, float e);

extern "C" LIB1_API int PrimeCount(int A, int B);