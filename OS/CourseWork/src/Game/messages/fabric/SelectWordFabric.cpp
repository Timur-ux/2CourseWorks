#include "Game/messages/fabric/SelectWordFabric.hpp"
#include "Game/messages/concretMessages/realizations/SelectWord.hpp"

game::message::fabric::request::SelectWord::SelectWord() {
	message = std::make_shared<message::request::SelectWord>();
}


message::fabric::IMessageFabric& game::message::fabric::request::SelectWord::configureFromRaw(pt::ptree data) {
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

	if (gameType != Type::selectWord) {
		throw std::invalid_argument("Game type not coinsiding");
	}

	return *this;
}

game::message::fabric::reply::SelectWord::SelectWord(long long id, std::string login, std::string word) {
	message = std::make_shared<message::reply::SelectWord>(id, login, word);
}

::message::fabric::IMessageFabric& game::message::fabric::reply::SelectWord::configureFromRaw(pt::ptree data) {
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

	if (gameType != Type::selectWord) {
		throw std::invalid_argument("Game type not coinsiding");
	}

	long long id = data.get<long long>("Game.Id");
	std::string login = data.get<std::string>("Game.Login");
	std::string word = data.get<std::string>("Game.Word");

	message = std::make_shared<message::reply::SelectWord>(id, login, word);
	return *this;
}