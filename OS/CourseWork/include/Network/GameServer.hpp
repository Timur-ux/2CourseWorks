#ifndef GAME_SERVER_H_
#define GAME_SERVER_H_

#include <string>
#include <iostream>

#include "Server.hpp"
#include "Game/GameLogger.hpp"

class GameServer : public Server {
public:
	GameServer(std::string IP, unsigned short port, IMessageManager& messageManager)
		: Server(IP, std::vector<unsigned short>{port, port + 1, port + 2}, messageManager) {
		isNowAuth = false;
		std::this_thread::sleep_for(100ms);
		std::thread(GameServer::startAuth, this);
	};

	void startAuth() override;
};

#endif