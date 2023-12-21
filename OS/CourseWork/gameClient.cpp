#include <iostream>
#include <string>
#include <memory>

#include "Client.hpp"
#include "Network/Socket.hpp"

std::shared_ptr<Socket> inputSocket();

int main() {
	std::cout << "Please, input server's IP and port(<IP>:<port>)" << std::endl;

	std::shared_ptr<Socket> socket = inputSocket();

	Client client()

	return 0;
}

std::shared_ptr<Socket> inputSocket() {
	std::shared_ptr<Socket> socket;
	std::string serverData;
	bool socketSetted = false;
	
	while (!socketSetted) {
		try {
			std::cin >> serverData;
			socket = std::make_shared<Socket>(serverData);
			socketSetted = true;
		}
		catch (std::invalid_argument& e) {
			std::cout << "Error: " << e.what() << std::endl
				<< "Please, reinput server's IP and port: ";
		}
	}

	return socket;
}