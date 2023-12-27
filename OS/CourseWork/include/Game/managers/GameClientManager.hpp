#ifndef GAME_CLIENT_MANAGER_H_
#define GAME_CLIENT_MANAGER_H_

#include "Network/managers/ClientManager.hpp"
#include "Network/interfaces/IClient.hpp"
#include "Game/messages/concretMessages/allConcretMessages.hpp"

#include <iostream>

class GameClientManager : public ClientManager {
public:
	GameClientManager(network::IClient & client) : ClientManager(client) {}

	void provideDisconnect();
	void provideGameStart();

	void visit(game::message::request::IGuessWord&) override;
	void visit(game::message::request::ISelectWord&) override;
};

#endif // !GAME_CLIENT_MANAGER_H_