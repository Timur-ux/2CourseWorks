#include "Messages/messageFabric/ConcretFabric/CreateNewGameFabric.hpp"
#include "Messages/concretMessages/realizations/CreateNewGame.hpp"

message::fabric::request::CreateNewGame::CreateNewGame(std::list<std::string> logins) {
	message = std::make_shared<message::request::CreateNewGame>(logins);
}

message::fabric::IMessageFabric& message::fabric::request::CreateNewGame::configureFromRaw(pt::ptree data)
{
	boost::optional<int> _type = data.get_optional<int>("Message.Type");
	if (!_type.has_value()) {
		throw std::invalid_argument("Type not found");
	}

	Type type = static_cast<Type>(_type.value());

	if (type != Type::createNewGame) {
		throw std::invalid_argument("Type not coinsiding");
	}

	std::list<std::string> logins;
	pt::ptree loginsData = data.get_child("Message.CreateNewGame.Logins");
	for (auto& loginData : loginsData) {
		logins.push_back(loginData.second.get_value<std::string>());
	}

	message = std::make_shared<message::request::CreateNewGame>(logins);
	return *this;
}