#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include "Server.hpp"
#include "MessageQueue.hpp"
#include "safeBool.hpp"
#include "MessageFormsGenerator.hpp"

#include <thread>
#include <map>
#include <string>
#include <list>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace pt = boost::property_tree;

class Player {
	long long id;
	std::string login;

	boost::optional<std::string> word = boost::none;
public:
	Player(long long _id, std::string _login) 
		: id(_id), login(_login) {}

	long long getId() const;
	std::string getLogin() const;
	boost::optional<std::string> getWord() const;

	std::pair<int, int> calcCowsAndBulls(std::string otherWord) const;

	void setWord(std::string _word);

};

class GameManager {
private:
	Server& server;
	long long gameId;

	std::map<std::string, Player> players;

	MessageQueue<pt::ptree> mq;
	SafeBool isNowSending{ false };

	void checkMessages();
	bool isGameRunning = false;
public:
	GameManager(Server& _server, long long _gameId) : server(_server), gameId(_gameId) {}

	void setPlayers(std::list<std::string> logins);
	void addPlayer(std::string login);

	void sendForAll(std::string message);
	void sendFor(std::string login, pt::ptree data);

	void startGame();

	void pushMessage(pt::ptree data);

	long long getGameId() const;

	void guessWord(std::string guessing, std::string guessed, std::string word);

};

#endif // !GAME_MANAGER_H_
