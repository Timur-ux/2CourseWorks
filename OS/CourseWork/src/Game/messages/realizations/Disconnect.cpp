#include "Game/messages/concretMessages/realizations/Disconnect.hpp"

pt::ptree game::message::request::Disconnect::getData() {
	pt::ptree data;
	data.put("Message.Type", static_cast<int>(::message::Type::gameAction));
	data.put("Message.GameAction", static_cast<int>(Type::disconnect));
	data.put("Message.ReqRepType", static_cast<int>(::message::ReqRepType::request));

	data.put("Game.Id", id);
	data.put("Game.Login", login);

	return data;
}