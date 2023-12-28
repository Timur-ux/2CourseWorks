#include "Messages/messageFabric/ConcretFabric/GetLoginsMessageFabric.hpp"
#include "Messages/concretMessages/realizations/GetLogins.hpp"

message::fabric::request::GetLogins::GetLogins(std::string login, long long id)
{
	message = std::make_shared<message::request::GetLogins>(id, login);
}

message::fabric::IMessageFabric& message::fabric::request::GetLogins::configureFromRaw(pt::ptree data)
{
	boost::optional<int> _type = data.get_optional<int>("Message.Type");
	if (!_type.has_value()) {
		throw std::invalid_argument("Type not found");
	}

	Type type = static_cast<Type>(_type.value());

	if (type != Type::getLogins) {
		throw std::invalid_argument("Type not coinsiding");
	}

	std::string login = data.get<std::string>("Message.GetLogins.Login");
	long long id = data.get<long long>("Message.GetLogins.Id");

	message = std::make_shared<message::request::GetLogins>(id, login);
	return *this;
}

message::fabric::reply::GetLogins::GetLogins(std::list<std::string> logins)
{
	message = std::make_shared<message::reply::GetLogins>(logins);
}

message::fabric::IMessageFabric& message::fabric::reply::GetLogins::configureFromRaw(pt::ptree data)
{
	boost::optional<int> _type = data.get_optional<int>("Message.Type");
	if (!_type.has_value()) {
		throw std::invalid_argument("Type not found");
	}

	Type type = static_cast<Type>(_type.value());

	if (type != Type::getLogins) {
		throw std::invalid_argument("Type not coinsiding");
	}

	std::list<std::string> logins;
	
	pt::ptree loginsData = data.get_child("Message.GetLogins.Logins");
	
	for (auto& loginData : loginsData) {
		logins.push_back(loginData.second.get_value<std::string>());
	}

	message = std::make_shared<message::reply::GetLogins>(logins);
	return *this;
}