#ifndef SIN_INTEGRAL_H_
#define SIN_INTEGRAL_H_
#include "realizationType.hpp"
#include <cmath>
#include <stdexcept>

__declspec(dllexport) float __cdecl SinIntegral(float A, float B, float e);

__declspec(dllexport) float __cdecl __SinIntegralOne(float A, float B, float e);

__declspec(dllexport) float __cdecl __SinIntegralTwo(float A, float B, float e);

#endif