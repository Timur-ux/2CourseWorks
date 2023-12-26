#include "Network/concretServers/Server.hpp"
#include "Network/managers/ServerManager.hpp"

#include <iostream>
#include <memory>

int main() {
	std::string IP = "127.0.0.1";
	network::PortsTriplet ports{2000, 2001, 2002};
	
	std::shared_ptr<network::IServer> server = std::make_shared<network::Server>(IP, ports);
	std::shared_ptr<network::ServerManager> manager = std::make_shared<network::ServerManager>(*server);

	manager->subscribeTo(server.get());

	std::thread(&network::IServer::startAuth, server).detach();
	server->startRecieving();

	return 0;
}