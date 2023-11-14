#include <iostream>
#include <sstream>
#include <windows.h>
#include <stdexcept>

typedef int (*void2int)(void);
typedef float (*fff2float)(float, float, float);
typedef int (*ii2int)(int, int);


void2int SinRealizationChange;
void2int PrimesRealizationChange;
int realizationChange();

int main() {
	HMODULE sinLib = LoadLibrary(TEXT("./build/libsin.dll"));
	if (sinLib == NULL) {
		std::cerr << "SinIntegralLib open error, errno = " << GetLastError() << std::endl;
	}

	HMODULE primesLib = LoadLibrary(TEXT("./build/libprimes.dll"));
	if (primesLib == NULL) {
		std::cerr << "PrimeCountLib open error, errno = " << GetLastError() << std::endl;
	}
	
	SinRealizationChange = (void2int)GetProcAddress(sinLib, "SinRealizationChange");
	if(SinRealizationChange == NULL) {
		std::cerr << "SinRealizationChange get adress error, errno = " << GetLastError() << std::endl;
	}

	PrimesRealizationChange = (void2int)GetProcAddress(primesLib, "PrimesRealizationChange");
	if(PrimesRealizationChange == NULL) {
		std::cerr << "PrimesRealizationChange get adress error, errno = " << GetLastError() << std::endl;
	}
	
	fff2float SinIntegral = (fff2float)GetProcAddress(sinLib, "SinIntegral");
	if(SinIntegral == NULL) {
		std::cerr << "SinIntegral get adress error, errno = " << GetLastError() << std::endl;
	}
	
	ii2int PrimeCount = (ii2int)GetProcAddress(primesLib, "PrimeCount");
	if(PrimeCount == NULL) {
		std::cerr << "PrimeCount get adress error, errno = " << GetLastError() << std::endl;
	}
	
	std::string command;
	while (std::getline(std::cin, command)) {
		if (command.size() == 1 && command[0] == '0') {
			int curRealization = realizationChange();
			std::cout << "Current realization is " << curRealization + 1 << std::endl;
			continue;
		}
		std::stringstream stream(command);
		int funcNumber;
		stream >> funcNumber;
		if (funcNumber == 1) {
			float A, B, e;
			stream >> A >> B >> e;
			std::cout << SinIntegral(A, B, e) << std::endl;
		}
		else if (funcNumber == 2) {
			int A, B;
			stream >> A >> B;
			std::cout << PrimeCount(A, B) << std::endl;
		}
	}
	return 0;
}

int realizationChange() {
	int res1 = SinRealizationChange();
	int res2 = PrimesRealizationChange();
	if(res1 != res2) {
		std::cerr << "Strange realization change result" << std::endl;
	}
	return res1;
}