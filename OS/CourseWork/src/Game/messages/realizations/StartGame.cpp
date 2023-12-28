#include "Game/messages/concretMessages/realizations/StartGame.hpp"

pt::ptree game::message::request::StartGame::getData() {
	pt::ptree data;
	data.put("Message.Type", static_cast<int>(::message::Type::gameAction));
	data.put("Message.GameAction", static_cast<int>(Type::startGame));
	data.put("Message.ReqRepType", static_cast<int>(::message::ReqRepType::request));

	data.put("Game.Id", id);
	data.put("Game.Login", login);

	return data;
}