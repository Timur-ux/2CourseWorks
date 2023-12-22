#include "Game/GameClientManager.hpp"

void GameClientManager::push(pt::ptree data) {
	boost::optional<std::string> type = data.get_optional<std::string>("Message.type");

	if (!type.has_value() || type.value() != "GameAction") {
		return;
	}

	game::Action action = data.get<game::Action>("Game.action.type");
	switch (action) {
	case game::Action::selectWord:
		std::string word;
		std::cout << "Please, select word(only first 4 letters will be selected): ";
		std::cin >> word;

		word = (word.size() > 4 ? word.substr(0, 4) : word);
		IForm former = game::reply::SelectWordForm(word, id, login);
		client->sendData(former.getForm());
		break;
	case game::Action::guessWord:
		std::string word, opponent;
		std::cout << "Please, select word(only first 4 letters will be selected) and opponent(login): ";
		std::cin >> word >> opponent;

		word = (word.size() > 4 ? word.substr(0, 4) : word);
		IForm former = game::reply::GuessWordForm(word, opponent, id, login);
		client->sendData(former.getForm());
		break;
	case game::Action::endGame:
		std::cout << "Game has finished, disconnecting..." << std::endl;
		client->disconnect();
	}
}

void GameClientManager::setClient(Client* client) {
	login = client->getLogin();
	id = client->getId();
}

void GameClientManager::startGame(std::list<std::string> logins) {
	IForm former = game::request::CreateNewGameForm(logins);

	client->sendData(former.getForm());

	std::thread(&Client::startRecieving, client);
}