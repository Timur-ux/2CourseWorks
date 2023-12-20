#include "Network/GameServer.hpp"
#include "Game/GameManager.hpp"
#include <iostream>

#include <boost/property_tree/ptree.hpp>

namespace pt = boost::property_tree;

int main(int argc, char* argw[]) {
	if (argc != 3) {
		throw std::invalid_argument("Usage: <program name> <IP adress> <free port>");
	}
	
	std::string IP = argw[1];
	unsigned short port = atoi(argw[2]);

	GameManager gameManager;
	GameServer server(IP, port, gameManager);

	gameManager.setServer(&server);

	int secondsLast = 60;
	while (secondsLast-- > 0) {
		GameLogger oss;
		oss << "Till game start " << secondsLast << " seconds last" << std::endl;
		IForm former = MessageForAll(oss.str());
		server.sendForAll(former.getForm());
	}

	gameManager.startGame();

	return 0;
}