#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include "Server.hpp"
#include "MessageQueue.hpp"
#include "safeBool.hpp"
#include "Messages/MessageFormsGenerator.hpp"
#include "Messages/MessageManager.hpp"

#include <thread>
#include <map>
#include <string>
#include <list>
#include <chrono>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace pt = boost::property_tree;
using namespace std::chrono_literals;

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

class GameManager : public IMessageManager {
private:
	std::map<std::string, Player> players;

	bool isGameRunning = false;
	Server* server = nullptr;

	int guessCounter = 0;
public:
	GameManager() = default;
	GameManager(Server * _server) {
		setServer(_server);
	}

	void setServer(Server* _server);
	
	void push(pt::ptree data) override;

	void sendForAll(pt::ptree data);
	void sendFor(std::string login, pt::ptree data);

	void startGame();
};

#endif // !GAME_MANAGER_H_
