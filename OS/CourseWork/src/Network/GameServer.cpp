#include "Network/GameServer.hpp"

void GameServer::startAuth()
{
	isNowAuth = true;
	while (isNowAuth) {
		pt::ptree data = provideAuthAndGetResult();

		boost::optional<bool> authStatus = data.get_optional<bool>("Auth.status");
		if (authStatus.has_value() && authStatus.value()) {
			GameLogger oss;
			std::string login = data.get<std::string>("Auth.login");
			oss << login << " has joined!" << std:endl;

			IForm former = MessageForAll(oss.str());
			sendForAll(former.getForm());
		}
	}
}
