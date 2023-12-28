#include "Game/messages/fabric/StartGameFabric.hpp"
#include "Game/messages/concretMessages/realizations/StartGame.hpp"

game::message::fabric::request::StartGame::StartGame(long long id, std::string login) {
	message = std::make_shared<message::request::StartGame>(id, login);
}

::message::fabric::IMessageFabric& game::message::fabric::request::StartGame::configureFromRaw(pt::ptree data) {
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

	if (gameType != Type::startGame) {
		throw std::invalid_argument("Game type not coinsiding");
	}

	long long id = data.get<long long>("Game.Id");
	std::string login = data.get<std::string>("Game.Login");

	message = std::make_shared<message::request::StartGame>(id, login);
	return *this;
}