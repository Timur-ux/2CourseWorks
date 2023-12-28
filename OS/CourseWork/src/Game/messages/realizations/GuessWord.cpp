#include "Game/messages/concretMessages/realizations/GuessWord.hpp"

pt::ptree game::message::request::GuessWord::getData() {
	pt::ptree data;
	data.put("Message.Type", static_cast<int>(::message::Type::gameAction));
	data.put("Message.GameAction", static_cast<int>(Type::guessWord));
	data.put("Message.ReqRepType", static_cast<int>(::message::ReqRepType::request));

	return data;
}


pt::ptree game::message::reply ::GuessWord::getData() {
	pt::ptree data;
	data.put("Message.Type", static_cast<int>(::message::Type::gameAction));
	data.put("Message.GameAction", static_cast<int>(Type::guessWord));
	data.put("Message.ReqRepType", static_cast<int>(::message::ReqRepType::reply));

	data.put("Game.Id", id);
	data.put("Game.Login", login);
	data.put("Game.Word", word);
	data.put("Game.Opponent", opponent);

	return data;
}