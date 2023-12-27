#include "Game/managers/GameClientManager.hpp"
#include "Network/concretServers/Client.hpp"

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
	std::cout << "[Game] Input word to select: ";
	std::string word;

	std::cin >> word;
	std::shared_ptr<::message::IMessage> message = ::message::fabric::MessageFabric::getInstance()
		.getRequest(
			game::message::fabric::request::StartGame(id, login)
		);

	client.send(*message);
}

void GameClientManager::visit(game::message::request::IGuessWord&)
{
	std::string opponent, word;
	std::cout << "[Game] Input opponent's login and word to guess: " << std::endl;
	std::cout << "Opponent: ";
	std::cin >> opponent;
	std::cout << "Word: ";
	std::cin >> word;

	std::shared_ptr<::message::IMessage> message = ::message::fabric::MessageFabric::getInstance()
		.getReply(
			game::message::fabric::reply::GuessWord(id, login, opponent, word)
		);

	client.send(*message);
}

void GameClientManager::visit(game::message::request::ISelectWord&)
{
	std::string word;
	std::cout << "[Game] Input word to select: " << std::endl;
	std::cout << "Word: ";
	std::cin >> word;

	std::shared_ptr<::message::IMessage> message = ::message::fabric::MessageFabric::getInstance()
		.getReply(
			game::message::fabric::reply::SelectWord(id, login, word)
		);

	client.send(*message);
}

void ClientManager::visit(message::reply::IInviteToGame& message) {
	int acceptCode = 1;
	std::cout << "Here invite to game, input " << acceptCode
		<< " to accept, any other -- to decline" << std::endl;

	int choosenCode;
	std::cin >> choosenCode;

	if (choosenCode == acceptCode) { 
		std::string IP = message.getGameServerIP();
		unsigned short authPort = message.getGameServerAuthPort();
		std::shared_ptr<network::IClient> gameClient = std::make_shared<network::Client>(IP, authPort);
		std::shared_ptr<GameClientManager> gameManager = std::make_shared<GameClientManager>(*gameClient);
	}
}
