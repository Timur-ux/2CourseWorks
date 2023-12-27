#include "Network/managers/ClientManager.hpp"
#include "Network/concretServers/Client.hpp"
#include "Game/managers/GameManager.hpp"

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

void ClientManager::provideAuth()
{
	std::string login;
	std::cout << "[Auth] Input login: " << login << std::endl;
	std::getline(std::cin, login);

	client.auth(login);
}

void ClientManager::provideGetLogins()
{
	std::shared_ptr<message::IMessage> message = message::fabric::MessageFabric::getInstance()
		.getRequest(
			message::fabric::request::GetLogins(login, id)
		);

	client.send(*message);
}

void ClientManager::provideCreateNewGame()
{
	std::cout << "¬ведите логин игрока, которого хотите пригласить." << std::endl;
	std::cout << "¬ведите \"Done\", чтобы начать игру" << std::endl;

	std::list<std::string> logins;
	std::string login;
	std::cout << ">>: ";
	std::getline(std::cin, login);
	while (login != "Done") {
		logins.push_back(login);
	}

	std::shared_ptr<message::IMessage> message = message::fabric::MessageFabric::getInstance()
		.getRequest(
			message::fabric::request::CreateNewGame(logins)
		);

	client.send(*message);
}

