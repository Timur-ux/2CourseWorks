#include "Network/managers/ClientManager.hpp"
#include "Network/concretServers/Client.hpp"
#include "Game/managers/GameManager.hpp"
#include "print.hpp"
#include "isNowScanning.hpp"

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
		print() << "Auth failed, please try again with another login" << std::endl;
		provideAuth();
		return;
	}

	id = message.getGivenId();
	login = message.getLogin();
	print() << "Auth succeed; given id: " << id 
		<< "; accepted login: " << login << std::endl;
}

void ClientManager::visit(message::reply::IGetLogins& message) {
	std::list<std::string> logins = message.getLogins();

	print() << "Here list of all authorized players:" << std::endl;
	
	int i = 1;
	for (auto& login : logins) {
		print() << i++ << ") " << login << std::endl;
	}
}

void ClientManager::provideAuth()
{
	std::string login;
	print() << "[Auth] Input login(1 word): " << login << std::endl;
	
	{
		std::unique_lock<std::mutex> lock(isNowScanning);
		std::cin >> login;
		while (login == "") {
			std::cin >> login;
		}
	}

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
	print() << "Input players login you want invite to." << std::endl;
	print() << "Input \"Done\", to begin game" << std::endl;

	std::list<std::string> logins;
	std::string login;

	{
		std::unique_lock<std::mutex> lock(isNowScanning);
		print() << ">>: ";
		std::cin >> login;
		while (login != "Done") {
			logins.push_back(login);
			print() << ">>: ";
			std::cin >> login;
		}
	}
	logins.push_back(this->login);

	std::shared_ptr<message::IMessage> message = message::fabric::MessageFabric::getInstance()
		.getRequest(
			message::fabric::request::CreateNewGame(id, this->login, logins)
		);

	client.send(*message);
}

