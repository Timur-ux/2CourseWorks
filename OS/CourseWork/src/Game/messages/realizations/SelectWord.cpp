#include "Game/messages/concretMessages/realizations/SelectWord.hpp"

pt::ptree game::message::request::SelectWord::getData() {
	pt::ptree data;
	data.put("Message.Type", static_cast<int>(::message::Type::gameAction));
	data.put("Message.GameAction", static_cast<int>(Type::selectWord));
	data.put("Message.ReqRepType", static_cast<int>(::message::ReqRepType::request));

	return data;
}

pt::ptree game::message::reply::SelectWord::getData() {
	pt::ptree data;
	data.put("Message.Type", static_cast<int>(::message::Type::gameAction));
	data.put("Message.GameAction", static_cast<int>(Type::selectWord));
	data.put("Message.ReqRepType", static_cast<int>(::message::ReqRepType::reply));

	data.put("Game.Login", login);
	data.put("Game.Id", id);
	data.put("Game.Word", word);

	return data;

}