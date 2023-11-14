#include <iostream>
#include <sstream>

extern "C" __declspec(dllimport) int __cdecl SinRealizationChange();
extern "C" __declspec(dllimport) int __cdecl PrimesRealizationChange();
extern "C" __declspec(dllimport) int __cdecl PrimeCount(int a, int B);
extern "C" __declspec(dllimport) float __cdecl SinIntegral(float a, float b, float e);

int realizationChange();

int main() {
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