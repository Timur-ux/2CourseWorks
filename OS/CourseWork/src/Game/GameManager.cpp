#include "Game/GameManager.hpp"
#include <algorithm>
#include <sstream>

#define min(a, b) (a < b ? a : b)
#define in(container, item) std::find(std::begin(container), std::end(container), item) != std::end(container)
#define find(container, item) std::find(std::begin(container), std::end(container), item)

void GameManager::setPlayers(std::list<std::string> logins)
{
	for (std::string& login : logins) {
		addPlayer(login);
	}
}

void GameManager::addPlayer(std::string login)
{
	boost::optional<long long> id = server.getIdByLogin(login);
	if (id) {
		players[login] = Player(id, login);
	}
}

void GameManager::sendForAll(pt::ptree data)
{
	if (server == nullptr) {
		printErr() << "Server not setted. Send for all declined" << std::endl;
	}

	server->sendForAll(data);
}

void GameManager::sendFor(std::string login, pt::ptree data)
{
	auto playerIt = find(players, login);
	if (playerIt == std::end(players)) {
		return;
	}

	long long id = playerIt->second.getId();

	server->sendTo(id, data);
}

void GameManager::startGame()
{	
	IForm former = MessageForAll("Game starts! Be ready!");
	sendForAll(former.getForm());

	former = GameActionRequest(GameAction::selectWord);
	
	sendForAll(former.getForm());

	std::this_thread::sleep_for(300ms);

	isGameRunning = true;
	while (isGameRunning) {
		former = MessageForAll("Game's round starts. Please select player to guess and word");
		sendForAll(former.getForm());

		guessCounter = 0;
		former = GameActionRequest(GameAction::guessWord);
		sendForAll(former.getForm());

		int timeSleep = 0;
		while (timeSleep < 60 && guessCounter < players.size()) {
			std::this_thread::sleep_for(1s);
			++timeSleep;
		}
	}
}

long long Player::getId() const
{
	return id;
}

std::string Player::getLogin() const
{
	return login;
}

boost::optional<std::string> Player::getWord() const
{
	return word;
}

std::pair<int, int> Player::calcCowsAndBulls(std::string otherWord) const
{
	int bulls = 0;
	int cows = 0;

	std::list<char> myWord = word.value().c_str();

	auto charIt = std::begin(myWord);
	for (int i = 0; i < min(myWord.size(), otherWord.size()); ++i, ++charIt) {
		if (*charIt == otherWord[i]) {
			++bulls;
		}
	}

	for (int i = 0; i < otherWord.size(); ++i) {
		char curChar = otherWord[i];

		auto charIt = find(myWord, curChar);
		if (charIt != std::end(myWord)) {
			++cows;
			myWord.erase(charIt);
		}
	}

	return std::make_pair<int, int>(cows, bulls);
}

void Player::setWord(std::string _word)
{
	word = _word;
}

void GameManager::setServer(Server* _server) {
	server = _server;
	std::map<std::string, long long> clients = server->getClients();

	for (auto& client : clients) {
		players[client.first] = Player(client.second, client.first);
	}
}

void GameManager::push(pt::ptree data) {

}