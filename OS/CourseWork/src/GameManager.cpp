#include "GameManager.hpp"
#include <algorithm>
#include <sstream>

#define min(a, b) (a < b ? a : b)
#define in(container, item) std::find(std::begin(container), std::end(container), item) != std::end(container)
#define find(container, item) std::find(std::begin(container), std::end(container), item)

void GameManager::checkMessages()
{
	for (int i = 0; i < mq.size(); ++i) {
		pt::ptree message = mq.front();
		mq.pop();

		boost::optional<GameAction> action = message.get_optional<GameAction>("Game.action.type");

		if (action) {
			switch (action.value()) {
			case GameAction::selectWord:
				boost::optional<std::string> word = message.get_optional<std::string>("Game.action.word");
				boost::optional<std::string> login = message.get_optional<std::string>("Game.login");
				
				if (word && login) {
					auto& player = find(players, login)->second;
					player.setWord(word.value());
				}
				break;
			case GameAction::guessWord:

			}
		}
	}
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

void GameManager::sendForAll(std::string message)
{
	IForm former = MessageForAll(message);
	pt::ptree data = former.getForm();
	data.put<long long>("Game.id", gameId);

	for (auto& player : players) {
		long long id = player.second.getId();

		server.sendTo(id, data);
	}
}

void GameManager::sendFor(std::string login, pt::ptree data)
{
	auto playerIt = find(players, login);
	if (playerIt == std::end(players)) {
		return;
	}

	long long id = playerIt->second.getId();

	server.sendTo(id, data);
}

void GameManager::startGame()
{
	std::thread(&GameManager::MessageSender, this).detach();
	
	sendForAll("Game begins, be ready!");

	IForm former = GameActionRequest(GameAction::selectWord);
	data = former.getForm();
	for (auto& player : players) {
		sendFor(player.first, data);
	}

	std::this_thread::sleep_for(300ms);

	isGameRunning = true;
	checkMessages();
	while (isGameRunning) {
		sendForAll("")
	}
}

void GameManager::pushMessage(pt::ptree data)
{
	mq.push(data);
}

long long GameManager::getGameId() const
{
	return gameId;
}

void GameManager::guessWord(std::string guessing, std::string guessed, std::string word)
{
	std::ostringstream oss;
	if (players[guessed].getWord() == word) {
		isGameRunning = false;
		oss << "Congratilations!!! " << guessing << " guess right word which"
			<< guessed << " select. The word: " << word << std::endl;
		sendForAll(oss.str())
	}
	else {
		auto cowsBulls = players[guessed].calcCowsAndBulls(word);
		oss << guessing << " try to guess word which " << guessed << "select. " 
			<< "Cows: " << cowsBulls.first << "; Bulls: " << cowsBulls.second << std::endl;
		sendForAll(oss.str())
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
