#include "Game/messages/fabric/GuessWordFabric.hpp"
#include "Game/messages/concretMessages/realizations/GuessWord.hpp"

game::message::fabric::request::GuessWord::GuessWord()
{
	message = std::make_shared<message::request::GuessWord>();
}

::message::fabric::IMessageFabric& game::message::fabric::request::GuessWord::configureFromRaw(pt::ptree data) {
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

	if (gameType != Type::guessWord) {
		throw std::invalid_argument("Game type not coinsiding");
	}

	message = std::make_shared<message::request::GuessWord>();
	return *this;
}

game::message::fabric::reply::GuessWord::GuessWord(long long id, std::string login, std::string word, std::string opponent) {
	message = std::make_shared<message::reply::GuessWord>(id, login, word, opponent);
}

::message::fabric::IMessageFabric& game::message::fabric::reply::GuessWord::configureFromRaw(pt::ptree data) {
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

	if (gameType != Type::guessWord) {
		throw std::invalid_argument("Game type not coinsiding");
	}

	long long id = data.get<long long>("Game.Id");
	std::string login = data.get<std::string>("Game.Login");
	std::string word = data.get<std::string>("Game.Word");
	std::string opponent = data.get<std::string>("Game.Opponent");

	message = std::make_shared<message::reply::GuessWord>(id, login, word, opponent);
	return *this;
}