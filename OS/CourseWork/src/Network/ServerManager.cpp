#include "Network/ServerManager.hpp"

void ServerManager::subscribeTo(message::IObserver* observer) {
	observer->subscribe(*this);
}

void ServerManager::notify(message::request::IMessage message) {
	message.accept(*this);
}

void ServerManager::visit(message::request::IAuth& message) {
	std::string login = message.getLogin();
	boost::optional<long long> id = server.getIdByLogin(login);
	
	if (!id.has_value()) {
		printLog() << "authentication: " << login << ". Status: failed" << std::endl;
		return;
	}

	clients[id.value()] = login;
}

void visit(message::request::IPing& message) {
	
}

