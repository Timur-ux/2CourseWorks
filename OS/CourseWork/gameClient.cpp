#include <iostream>
#include <string>
#include <memory>
#include <list>

#include "Client.hpp"
#include "Game/GameClientManager.hpp"
#include "Network/Socket.hpp"

std::shared_ptr<Socket> inputSocket();

int main() {
	std::cout << "Please, input server's IP and auth port(<IP>:<port>)" << std::endl;

	std::shared_ptr<Socket> socket = inputSocket();
	GameClientManager gameClientManager;

	Client client(socket->IP, socket->port, gameClientManager);

	{
		std::string login;
		std::cout << "Please choose your login: ";
		std::cin >> login;
		
		bool authStatus = client.auth(login);
		while (!authStatus) {
			std::cout << "The choosen login not corresponding, please choose another one: ";
			std::cin >> login;
			authStatus = client.auth(login);
		}

		std::cout << "Auth succeed" << std::endl;
		gameClientManager.setClient(&client);
	}

	while (true) {
		std::list<std::string> players = { client.getLogin() };

		while (true) {
			std::cout << "1. Invite new player" << std::endl
				<< "2. Start game" << std::endl
				<< "3. Quit" << std::endl;
			int choose;
			std::cin >> choose;
			switch (choose) {
			case 1:
				std::string login;
				std::cout << "Input player's login to invite him: ";
				std::cin >> login;

				players.push_back(login);
				break;
			case 2:

			}
		}
		
	}
	
	

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