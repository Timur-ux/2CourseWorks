#include "Messages/concretMessages/realizations/CreateNewGame.hpp"

pt::ptree message::request::CreateNewGame::getData()
{
	pt::ptree data;
	data.put<int>("Message.Type", static_cast<int>(Type::createNewGame));
	data.put<int>("Message.ReqRepType", static_cast<int>(ReqRepType::request));
	
	pt::ptree loginsData;
	for (auto& login : logins) {
		pt::ptree child;
		child.put("", login);
		loginsData.push_back({ "", child });
	}

	data.add_child("Message.CreateNewGame.Logins", loginsData);

	return data;
}