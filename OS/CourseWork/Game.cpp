#include "Network/concretServers/Server.hpp"
#include "Game/managers/GameManager.hpp"

int main(int argc, char* argw[]) {
	if (argc != 5) {
		throw std::invalid_argument("Usage <program name> <IP> <port1> <port2> <port3>");
	}

	std::string IP = argw[1];
	network::PortsTriplet ports{atoi(argw[2]), atoi(argw[3]), atoi(argw[4])};

	std::shared_ptr<network::IServer> server = std::make_shared<network::Server>(IP, ports);
	std::shared_ptr<game::GameManager> gameManager = std::make_shared<game::GameManager>(*server);

	gameManager->subscribeTo(server.get());

	std::thread(&network::IServer::startAuth, server).detach();
	server->startRecieving();

	return 0;
}