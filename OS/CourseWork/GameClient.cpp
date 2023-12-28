#include "Network/managers/ClientManager.hpp"
#include "Network/concretServers/Client.hpp"

#include "isNowScanning.hpp"
#include "print.hpp"

#include <iostream>
#include <thread>

using namespace std::chrono_literals;

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
	try {
		manager->provideAuth();
	}
	catch(std::exception & e) {
		print() << "Error: " << e.what() << std::endl;
	}

	std::thread(&network::IClient::startRecieving, client).detach();

	while (true) {
		std::this_thread::sleep_for(5s);
		print() << "Please select action(action number): " << '\n'
			<< "1) Get list of authorized players logins" << '\n'
			<< "2) Choose players and create new game" << '\n'
		<< "3) Wait 5 seconds while something may happen" << '\n';
		
		int choose;
		
		{
			std::unique_lock<std::mutex> lock(isNowScanning);
			std::cin >> choose;
		}
		

		switch (choose) {
		case 1:
			manager->provideGetLogins();
			break;
		case 2:
			manager->provideCreateNewGame();
			break;
		case 3:
			std::this_thread::sleep_for(5s);
			break;
		default:
			print() << "Undefined action please choose again\n";
		}
	}

	return 0;
}