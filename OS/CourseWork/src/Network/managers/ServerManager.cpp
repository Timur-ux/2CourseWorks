#include "Network/managers/ServerManager.hpp"
#include "Game/GameProcessCreator.hpp"

#define in(container, item) std::find(std::begin(container), std::end(container), item) != std::end(container)

void ServerManager::subscribeTo(message::IObserver* observer) {
	observer->subscribe(*this);
}

void ServerManager::notify(message::IMessage &message) {
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

void ServerManager::visit(message::request::IGetLogins& message) {
	std::list<std::string> logins;
	for (auto& client : clients) {
		logins.push_back(client.second);
	}

	std::shared_ptr<message::IMessage> reply = message::fabric::MessageFabric::getInstance()
		.getReply(message::fabric::reply::GetLogins(logins));

	server.sendFor(message.getId(), *reply);
}

void ServerManager::visit(message::request::ICreateNewGame& message) {
	std::string IP = "127.0.0.1";
	unsigned short authPort = freePort++;
	GameProcessCreator::createNewGameProcess(IP, { authPort, freePort++, freePort++ });

	std::shared_ptr<message::IMessage> reply = message::fabric::MessageFabric::getInstance()
		.getReply(message::fabric::reply::InviteToGame(IP, authPort));

	std::list<std::string> logins = message.getLogins();
	
	for (auto& client : clients) {
		if (in(logins, client.second)) {
			server.sendFor(client.first, *reply);
		}
	}
}



