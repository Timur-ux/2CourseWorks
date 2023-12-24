#include "Game/managers/GameManager.hpp"
#include "Messages/messageFabric/MessageFabric.hpp"
#include <iostream>
#include <sstream>

using namespace game;

void GameManager::subscribeTo(::message::IObserver* observer) {
	observer->subscribe(*this);
}

void GameManager::notify(::message::IMessage& message) {
	message.accept(*static_cast<message::request::IGameMessageVisitor*>(this));
	message.accept(*static_cast<message::reply::IGameMessageVisitor*>(this));
}

void GameManager::visit(message::request::IStartGame&) {
	if (isNowGameRunning) {
		return;
	}

	isNowGameRunning = true;

	std::thread(&GameManager::provideGame, this).detach();
}

void GameManager::provideGame() {
	server.sendForAll(::message::DataMessage("Game has started, be ready!"));

	std::shared_ptr<::message::IMessage> request = ::message::fabric::MessageFabric::getInstance()
		.getRequest(
			game::message::fabric::request::SelectWord()
	);

	server.sendForAll(::message::DataMessage("Please, select word for 2 minutes"));
	server.sendForAll(*request);

	std::this_thread::sleep_for(120s);

	while (isNowGameRunning) {
		server.sendForAll(::message::DataMessage("New round start, please choose opponent and word to guess for 2 minute"));
		
		request = ::message::fabric::MessageFabric::getInstance()
			.getRequest(
				game::message::fabric::request::GuessWord()
		);
		server.sendForAll(*request);

		std::this_thread::sleep_for(120s);
	}

	server.sendForAll(::message::DataMessage("Game has finished, thanks for you time"));
}


void GameManager::visit(message::request::IDisconnect& message) {
	long long id = message.getId();

	auto clientIt = clients.find(id);
	if (clientIt == std::end(clients)) {
		return;
	}

	Player& player = clientIt->second;

	server.sendForAll(::message::DataMessage(player.getLogin() + ": disconnected"));

	clients.erase(clientIt);
}

void GameManager::visit(message::reply::ISelectWord& message) {
	long long id = message.getId();
	std::string login = message.getLogin();
	std::string word = message.getWord();

	auto clientIt = clients.find(id);
	if (clientIt == std::end(clients)) {
		return;
	}

	Player& player = clientIt->second;
	player.setWord(word);

	server.sendForAll(::message::DataMessage(login + ": select word right now"));
}

void GameManager::visit(message::reply::IGuessWord& message) {
	long long id = message.getId();
	std::string login = message.getLogin();
	std::string word = message.getWord();
	std::string opponent = message.getOpponent();
	boost::optional<std::string> opponentWord;

	auto clientIt = std::end(clients);
	for (auto client = std::begin(clients); client != std::end(clients); ++client) {
		if (client->second.getLogin() == opponent) {
			clientIt = client;
		}
	}
	
	if (clientIt == std::end(clients)) {
		return;
	}

	std::ostringstream oss;
	opponentWord = clientIt->second.getSelectedWord();
	if (opponentWord == word) {
		oss << "Congratulations! " << login << " right guess "
			<< opponent << " word. Word: " << word << std::endl;
		server.sendForAll(
			::message::DataMessage(oss.str())
		);

		isNowGameRunning = false;
		return;
	}
	auto cowsAndBulls = clientIt->second.calcCowsAndBulls(word);

	oss << login << "has guessed " << opponent << " word" << std::endl
		<< "Word: " << word << "; Cows: " << cowsAndBulls.first
		<< "; Bulls: " << cowsAndBulls.second << std::endl;

	server.sendForAll(
		::message::DataMessage(oss.str())
	);
}

