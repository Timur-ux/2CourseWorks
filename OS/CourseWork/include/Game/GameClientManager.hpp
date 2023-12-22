#ifndef GAME_CLIENT_MANAGER_H_
#define GAME_CLIENT_MANAGER_H_

#include "Messages/MessageManager.hpp"
#include "Network/Client.hpp"

#include <string>
#include <boost/property_tree/ptree.hpp>

class GameClientManager : public IMessageManager {
private:
	Client* client = nullptr;

	std::string login;
	long long id;
public:
	GameClientManager() = default;

	void push(pt::ptree data) override;

	void setClient(Client* client);

	void startGame(std::list<std::string> logins);
};

#endif