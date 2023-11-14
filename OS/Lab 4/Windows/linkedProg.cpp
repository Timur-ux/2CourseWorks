#include <iostream>
#include <sstream>

__declspec(dllimport) int realizationChange();
__declspec(dllimport) float __cdecl SinIntegral(float A, float B, float e);
__declspec(dllimport) int PrimeCount(int A, int B);

int main() {
	std::string command;
	while (std::getline(std::cin, command)) {
		if (command.size() == 1 and command[0] == '0') {
			int curRealization = realizationChange();
			std::cout << "Current realization is " << curRealization << std::endl;
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