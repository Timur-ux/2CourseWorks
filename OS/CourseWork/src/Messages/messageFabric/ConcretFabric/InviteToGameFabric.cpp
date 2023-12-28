#include "Messages/messageFabric/ConcretFabric/InviteToGameFabric.hpp"
#include "Messages/concretMessages/realizations/InviteToGame.hpp"

message::fabric::reply::InviteToGame::InviteToGame(std::string gameServerIP, unsigned short gameServerAuthPort) {
	message = std::make_shared<::message::reply::InviteToGame>(gameServerIP, gameServerAuthPort);
}

message::fabric::IMessageFabric& message::fabric::reply::InviteToGame::configureFromRaw(pt::ptree data) {
	boost::optional<int> _type = data.get_optional<int>("Message.Type");
	if (!_type.has_value()) {
		throw std::invalid_argument("Type not found");
	}

	Type type = static_cast<Type>(_type.value());

	if (type != Type::inviteToGame) {
		throw std::invalid_argument("Type not coinsiding");
	}

	std::string serverIP = data.get<std::string>("Message.InviteToGame.ServerIP");
	unsigned short authPort = data.get<unsigned short>("Message.InviteToGame.AuthPort");
	
	message = std::make_shared<::message::reply::InviteToGame>(serverIP, authPort);
	return *this;
}