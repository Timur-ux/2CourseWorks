#include "Network/managers/ClientManager.hpp"
#include <sstream>
#include <iostream>

void ClientManager::subscribeTo(message::IObserver* observer) {
	observer->subscribe(*this);
}

void ClientManager::notify(message::IMessage message) {
	message.accept(*static_cast<message::request::IMessageVisitor*>(this));
	message.accept(*static_cast<message::reply::IMessageVisitor*>(this));
}

void ClientManager::visit(message::request::IPing& message) {
	message::IMessage reply = message::fabric::MessageFabric
		::getInstance().getReply(
			message::fabric::reply::Ping(id, login);
	);

	client.send(reply);
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

