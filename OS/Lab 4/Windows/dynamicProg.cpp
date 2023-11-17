#include <iostream>
#include <sstream>
#include <windows.h>
#include <stdexcept>

typedef int (*void2int)(void);
typedef float (*fff2float)(float, float, float);
typedef int (*ii2int)(int, int);


fff2float SinIntegral;
ii2int PrimeCount;

static int currentRealization = 1;
int realizationChange();

HMODULE dllLibrary = NULL;

int main() {
	realizationChange();
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
	if (dllLibrary != NULL && !(FreeLibrary(dllLibrary))) {
		std::cerr << "Free library error" << std::endl;
	}
	currentRealization = (currentRealization + 1) % 2;
	
	if (currentRealization == 0) {
		dllLibrary = LoadLibrary(TEXT("./lib_one.dll"));
	}
	else if (currentRealization == 1) {
		dllLibrary = LoadLibrary(TEXT("./lib_two.dll"));
	}

	if (dllLibrary == NULL) {
		std::cerr << "LoadLibrary error, errno = " << GetLastError() << std::endl;
	}

	SinIntegral = (fff2float)GetProcAddress(dllLibrary, "SinIntegral");
	if (SinIntegral == NULL) {
		std::cerr << "SinIntegral load error, errno = " << GetLastError() << std::endl;
	}

	PrimeCount = (ii2int)GetProcAddress(dllLibrary, "PrimeCount");
	if (PrimeCount == NULL) {
		std::cerr << "PrimeCount load error, errno = " << GetLastError() << std::endl;
	}

	return currentRealization;
}