#include "Messages/messageFabric/ConcretFabric/CreateNewGameFabric.hpp"
#include "Messages/concretMessages/realizations/CreateNewGame.hpp"

message::fabric::request::CreateNewGame::CreateNewGame(long long id, std::string login, std::list<std::string> logins) {
	message = std::make_shared<message::request::CreateNewGame>(id, login, logins);
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

	long long id = data.get<long long>("Message.CreateNewGame.Id");
	std::string login = data.get<std::string>("Message.CreateNewGame.Login");
	std::list<std::string> logins;
	pt::ptree loginsData = data.get_child("Message.CreateNewGame.Logins");
	for (auto& loginData : loginsData) {
		logins.push_back(loginData.second.get_value<std::string>());
	}

	message = std::make_shared<message::request::CreateNewGame>(id, login, logins);
	return *this;
}