#include "Game/managers/GameManager.hpp"
#include "Messages/messageFabric/MessageFabric.hpp"
#include <iostream>
#include <sstream>

using namespace game;

void GameManager::subscribeTo(::message::IObserver* observer) {
	observer->subscribe(*this);
}

void GameManager::notify(std::shared_ptr<::message::IMessage> message) {
	message->accept(*this);
}

void GameManager::visit(message::request::IStartGame&) {
	if (state.load(std::memory_order_relaxed) == State::GameRunning) {
		return;
	}

	state.store(State::GameRunning, std::memory_order_relaxed);

	std::thread(&GameManager::provideGame, this).detach();
}

void GameManager::provideGame() {
	auto dataMessage = ::message::DataMessage("Game has started, be ready!");
	server.sendForAll(dataMessage);

	std::shared_ptr<::message::IMessage> request = ::message::fabric::MessageFabric::getInstance()
		.getRequest(
			game::message::fabric::request::SelectWord()
	);

	dataMessage = ::message::DataMessage("Please, select word for 2 minutes");
	server.sendForAll(dataMessage);
	server.sendForAll(*request);

	std::this_thread::sleep_for(120s);

	while (state.load(std::memory_order_relaxed) == State::GameRunning) {
		dataMessage = ::message::DataMessage("New round start, please choose opponent and word to guess for 2 minute");
		server.sendForAll(dataMessage);
		
		request = ::message::fabric::MessageFabric::getInstance()
			.getRequest(
				game::message::fabric::request::GuessWord()
		);
		server.sendForAll(*request);

		std::this_thread::sleep_for(120s);
	}

	dataMessage = ::message::DataMessage("Game has finished, thanks for you time");
	server.sendForAll(dataMessage);
}


void GameManager::visit(message::request::IDisconnect& message) {
	long long id = message.getId();

	auto clientIt = clients.find(id);
	if (clientIt == std::end(clients)) {
		return;
	}

	Player& player = clientIt->second;

	auto dataMessage = ::message::DataMessage(player.getLogin() + ": disconnected");
	server.sendForAll(dataMessage);

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

	auto dataMessage = ::message::DataMessage(login + ": select word now");
	server.sendForAll(dataMessage);
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
		auto dataMessage = ::message::DataMessage(oss.str());
		server.sendForAll(dataMessage);

		state.store(State::Preparing, std::memory_order_relaxed);
		return;
	}
	auto cowsAndBulls = clientIt->second.calcCowsAndBulls(word);

	oss << login << "has guessed " << opponent << " word" << std::endl
		<< "Word: " << word << "; Cows: " << cowsAndBulls.first
		<< "; Bulls: " << cowsAndBulls.second << std::endl;

	auto dataMessage = ::message::DataMessage(oss.str());
	server.sendForAll(dataMessage);
}

