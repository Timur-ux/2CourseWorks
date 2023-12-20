#include "Game/GameManager.hpp"
#include <algorithm>
#include <sstream>

#define min(a, b) (a < b ? a : b)
#define in(container, item) std::find(std::begin(container), std::end(container), item) != std::end(container)
#define find(container, item) std::find(std::begin(container), std::end(container), item)

GameManager::~GameManager() {
	IForm former = game::request::Form(game::Action::endGame);

	sendForAll(former.getForm());
}

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
	IForm former = MessageForAll("Game starts! Be ready! Please select word, game starts for 20 seconds");
	sendForAll(former.getForm());

	former = game::request::Form(game::Action::selectWord);
	sendForAll(former.getForm());

	std::this_thread::sleep_for(300ms);

	isNowGameRunning = true;
	while (isNowGameRunning) {
		former = MessageForAll("Game's round starts. Please select player to guess and word for 1 minute");
		sendForAll(former.getForm());

		guessCounter = 0;
		former = game::request::Form(game::Action::guessWord);
		sendForAll(former.getForm());

		int timeSleep = 0;
		while (timeSleep < 60 && guessCounter < players.size()) {
			std::this_thread::sleep_for(1s);
			++timeSleep;
		}
	}

	GameLogger oss;
	oss << "Game has finished, thanks for all" << std::endl;
	IForm former = MessageForAll(oss.str());

	sendForAll(former.getForm());
}

pt::ptree checkWord(Player& player, std::string word);
void GameManager::push(pt::ptree data) {
	boost::optional<std::string> type = data.get_optional<std::string>("Message.type");

	if (!type.has_value() || type != "GameAction") {
		return;
	}

	boost::optional<game::Action> action = data.get_optional<game::Action>("Game.action.type");
	boost::optional<std::string> login = data.get_optional<std::string>("Game.login");

	if (!action.has_value() || !login.has_value()) {
		return;
	}

	Player& player = players[login];

	switch (action.value()) {
	case game::Action::selectWord:
		boost::optional<std::string> word = player.getWord();
		if (word.has_value()) {
			return;
		}
		std::string wordToSet = data.get<std::string>("Game.action.word");
		player.setWord(wordToSet);
		break;
	case game::Action::guessWord:
		std::string opponentLogin = data.get<std::string>("Game.action.opponent");
		std::string wordToGuess = data.get<std::string>("Game.action.word");

		Player& opponent = players[opponentLogin];
		pt::ptree checkResult = checkWord(opponent, wordToGuess);

		GameLogger oss;

		if (checkResult.get<bool>("CheckWord.status")) {
			oss << "Congratulations!!! " << login
				<< " right guessed word that" << opponent << " selected." << std::endl
				<< "This word was " << wordToGuess << std::endl;
			isNowGameRunning = false;
		}
		else {
			int cows = checkResult.get<int>("CheckWord.cows");
			int bulls = checkResult.get<int>("CheckWord.bulls");
			oss << login << " unsuccessfully tried to guess word that "
				<< opponentLogin << " selected." << std::endl
				<< "Word: " << wordToGuess << ". Cows: " << cows << ". Bulls: " << bulls << std::endl;
		}

		IForm former = MessageForAll(oss.str());
		sendForAll(former.getForm());
		++guessCounter;
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
	if (!word.has_value()) {
		return std::make_pair<int, int>(0, 0);
	}

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

pt::ptree checkWord(Player& player, std::string word) {
	pt::ptree data;
	bool status = false;
	int bulls = 0;
	int cows = 0;

	std::pair<int, int> result = opponent.calcCowsAndBulls(wordToGuess);

	boost::optional<std::string> playerWord = player.getWord();
	if (playerWord.has_value()) {
		if (playerWord == word) {
			status = true;
		}

		cows = result.first;
		bulls = result.second;
	}

	data.put<bool>("CheckWord.status", status);
	data.put<int>("CheckWord.cows", cows);
	data.put<int>("CheckWord.bulls", bulls);

	return data;
}