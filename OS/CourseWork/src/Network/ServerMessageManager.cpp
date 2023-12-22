#include "Network/ServerMessageManager.hpp"
#include <list>

void ServerMessageManager::push(pt::ptree data) {
	boost::optional<std::string> type = data.get_optional<std::string>("Message.type");
	if (!type.has_value()) {
		print() << "Message.type not found! Message: " << data << std::endl;
		return;
	}

	if (type.value() != "RequestToServer") {
		print() << "Undefiend Message.type! Message: " << data << std::endl;
		return;
	}

	game::RequestToServer requestType = static_cast<game::RequestToServer>(data.get<int>("Request.type"));
	
	switch (requestType) {
	case game::RequestToServer::getLoginsList:
		auto& clientsData = server->getClients();
		std::list<std::string> logins;
		for (auto& client : clientsData) {
			logins.push_back(client.first);
		}

		IForm former = game::reply::GetLoginsListForm(logins);
	}
}

void ServerMessageManager::setServer(Server* server) {
	this->server = server;
}