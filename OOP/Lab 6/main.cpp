#include <iostream>
#include <memory>
#include "redactorBuilder.hpp"
#include "LocationRedactor.hpp"

RedactorDirector director;
Builder redactorBuilder;
std::string fileLogName = "LocationRedactor.log";

int main() {
	auto logFile = std::make_shared<std::ofstream>(fileLogName);
	std::shared_ptr<LocationRedactor> redactor = director.createDangeonRedactor(redactorBuilder, logFile, true);

	std::cout << "Command list here: " << std::endl;
	redactor->inputCommand("print commands list");
	std::cout << std::endl;

	while (true) {
		std::cout << "Input command(\"Exit\" for exit): ";
		std::string command;

		getline(std::cin, command);

		if (command == "") {
			getline(std::cin, command);
		}
		else if (command == "Exit") {
			break;
		}

		try {
			redactor->inputCommand(command);
		}
		catch (std::invalid_argument & e) {
			std::cout << "Error: " << e.what() << std::endl;
			continue;
		}
	}

	return 0;
}