#include "Network/managers/ClientManager.hpp"
#include <sstream>
#include <iostream>

void ClientManager::subscribeTo(message::IObserver* observer) {
	observer->subscribe(*this);
}

void ClientManager::notify(std::shared_ptr<message::IMessage> message) {
	message->accept(*this);
}

void ClientManager::visit(message::request::IPing& message) {
	auto reply = message::fabric::MessageFabric
		::getInstance().getReply(
			message::fabric::reply::Ping(id, login)
	);

	client.send(*reply);
}

void ClientManager::visit(message::reply::IAuth& message) {
	if (message.getAuthStatus() == false) {
		std::cout << "Auth failed, please try again with another login" << std::endl;
		provideAuth();
		return;
	}

	id = message.getGivenId();
	login = message.getLogin();
	std::cout << "Auth succeed; given id: " << id 
		<< "; accepted login: " << login << std::endl;
}

void ClientManager::visit(message::reply::IGetLogins& message) {
	std::list<std::string> logins = message.getLogins();

	std::cout << "Here list of all authorized players:" << std::endl;
	
	int i = 1;
	for (auto& login : logins) {
		std::cout << i++ << ") " << login << std::endl;
	}
}

void ClientManager::visit(message::reply::IInviteToGame& message) {
	int acceptCode = 1;
	std::cout << "Here invite to game, input " << acceptCode
		<< " to accept, any other -- to decline" << std::endl;

	int choosenCode;
	std::cin >> choosenCode;

	if (choosenCode == acceptCode) { // TODO: rewrite to create inner client, client game manager and provide all game here
		std::string IP = message.getGameServerIP();
		unsigned short authPort = message.getGameServerAuthPort();
		client.connectTo(IP, authPort);

		std::cout << "Provide authentication on game server..." << std::endl;
		client.auth(login);
	}
}

void ClientManager::provideAuth()
{
	std::string login;
	std::cout << "[Auth] Input login: " << login << std::endl;
	std::getline(std::cin, login);

	client.auth(login);
}

