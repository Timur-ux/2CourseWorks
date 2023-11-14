#ifndef SIN_INTEGRAL_H_
#define SIN_INTEGRAL_H_
#include <cmath>
#include <stdexcept>

static int realizationType = 0;

extern "C" __declspec(dllexport) int __cdecl SinRealizationChange();

extern "C" __declspec(dllexport) float __cdecl SinIntegral(float A, float B, float e);

float __cdecl __SinIntegralOne(float A, float B, float e);

float __cdecl __SinIntegralTwo(float A, float B, float e);

#endif