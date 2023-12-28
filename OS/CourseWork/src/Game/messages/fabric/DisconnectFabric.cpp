#include "Game/messages/fabric/DisconnectFabric.hpp"
#include "Game/messages/concretMessages/realizations/Disconnect.hpp"

game::message::fabric::request::Disconnect::Disconnect(long long id, std::string login) {
	message = std::make_shared<message::request::Disconnect>(id, login);
}

::message::fabric::IMessageFabric& game::message::fabric::request::Disconnect::configureFromRaw(pt::ptree data) {
	boost::optional<int> _type = data.get_optional<int>("Message.Type");
	if (!_type.has_value()) {
		throw std::invalid_argument("Type not found");
	}

	::message::Type type = static_cast<::message::Type>(_type.value());

	if (type != ::message::Type::gameAction) {
		throw std::invalid_argument("Type not coinsiding");
	}

	boost::optional<int> _gameType = data.get_optional<int>("Message.GameAction");
	if (!_gameType.has_value()) {
		throw std::invalid_argument("GameAction not found");
	}

	Type gameType = static_cast<Type>(_gameType.value());

	if (gameType != Type::disconnect) {
		throw std::invalid_argument("Game type not coinsiding");
	}

	long long id = data.get<long long>("Game.Id");
	std::string login = data.get<std::string>("Game.Login");

	message = std::make_shared<message::request::Disconnect>(id, login);
	return *this;
}