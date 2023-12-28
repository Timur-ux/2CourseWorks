#include "Game/managers/GameClientManager.hpp"
#include "Network/concretServers/Client.hpp"
#include "print.hpp"
#include <iostream>

void GameClientManager::provideDisconnect()
{
	std::shared_ptr<::message::IMessage> message = ::message::fabric::MessageFabric::getInstance()
		.getRequest(
			game::message::fabric::request::Disconnect(id, login)
		);

	client.send(*message);
}

void GameClientManager::provideGameStart()
{
	std::shared_ptr<::message::IMessage> message = ::message::fabric::MessageFabric::getInstance()
		.getRequest(
			game::message::fabric::request::StartGame(id, login)
		);

	client.send(*message);
}

void GameClientManager::visit(game::message::request::IGuessWord&)
{
	std::string opponent, word;
	print() << "[Game] Input opponent's login and word to guess: " << std::endl;
	print() << "Opponent: ";
	std::cin >> opponent;
	print() << "Word: ";
	std::cin >> word;

	std::shared_ptr<::message::IMessage> message = ::message::fabric::MessageFabric::getInstance()
		.getReply(
			game::message::fabric::reply::GuessWord(id, login, word, opponent)
		);

	client.send(*message);
}

void GameClientManager::visit(game::message::request::ISelectWord&)
{
	std::string word;
	print() << "[Game] Input word to select: " << std::endl;
	print() << "Word: ";
	std::cin >> word;

	std::shared_ptr<::message::IMessage> message = ::message::fabric::MessageFabric::getInstance()
		.getReply(
			game::message::fabric::reply::SelectWord(id, login, word)
		);

	client.send(*message);
}

void ClientManager::visit(message::reply::IInviteToGame& message) {
	int acceptCode = 1;
	print() << "Here invite to game, input " << acceptCode
		<< " to accept, any other -- to decline" << std::endl;

	int choosenCode;
	std::cin >> choosenCode;

	if (choosenCode == acceptCode) { 
		std::string IP = message.getGameServerIP();
		unsigned short authPort = message.getGameServerAuthPort();
		std::shared_ptr<network::IClient> gameClient = std::make_shared<network::Client>(IP, authPort);
		std::shared_ptr<GameClientManager> gameManager = std::make_shared<GameClientManager>(*gameClient);

		gameManager->subscribeTo(gameClient.get());
		gameManager->provideAuth();
		std::thread(&network::IClient::startRecieving, gameClient);
		gameManager->provideGameStart();
	}
}
