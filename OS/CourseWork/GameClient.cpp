#include "Network/managers/ClientManager.hpp"
#include "Network/concretServers/Client.hpp"

#include <iostream>

void chooseAction();

int main() {
	std::string IP;
	unsigned short port;

	std::cout << "Input server's IP: ";
	std::cin >> IP;
	std::cout << "Input server's port: ";
	std::cin >> port;

	std::shared_ptr<network::IClient> client = std::make_shared<network::Client>(IP, port);
	std::shared_ptr<ClientManager> manager = std::make_shared<ClientManager>(*client);

	manager->subscribeTo(client.get());
	manager->provideAuth();

	std::thread(&network::IClient::startRecieving, client).detach();

	while (true) {

	}

	return 0;
}

void chooseAction() {
	std::cout << "Выберите действие:" << std::endl;

	std::cout << "1) Получить список логинов" << std::endl;
	std::cout << "2) Начать игру" << std::endl;


}