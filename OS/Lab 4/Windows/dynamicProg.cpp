#include <iostream>
#include <windows.h>

HANDLE sinLib = LoadLibrary("libsin.dll");
HANDLE primesLib = LoadLibrary("libprimes.dll");

int main() {
	int (*realizationChange)(void) = (int(*)())GetProcAddress(sinLib, "realizationChange");
	float (*SinIntegral)(float, float, float) = (float(*)(float, float, float))GetProcAddress(sinLib, "SinIntegral");
	int (*PrimesCount)(int, int) = (int(*)(int, int))GetProcAddress(primesLib, "PrimesCount");
	return 0;
}