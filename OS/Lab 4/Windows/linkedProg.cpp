#include <iostream>
#include <sstream>
#include "./dll_sources/include/lib2.hpp"

int main() {
	std::string command;
	while (std::getline(std::cin, command)) {
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