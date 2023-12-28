#include "Messages/messageFabric/ConcretFabric/AuthMessageFabric.hpp"
#include "Messages/concretMessages/realizations/AuthMessage.hpp"

message::fabric::request::Auth::Auth(std::string login) {
	message = std::make_shared<message::request::Auth>(login);
}

message::fabric::IMessageFabric& message::fabric::request::Auth::configureFromRaw(pt::ptree data)
{
	boost::optional<int> _type = data.get_optional<int>("Message.Type");
	if (!_type.has_value()) {
		throw std::invalid_argument("Type not found");
	}

	Type type = static_cast<Type>(_type.value());

	if (type != Type::auth) {
		throw std::invalid_argument("Type not coinsiding");
	}

	std::string login = data.get<std::string>("Message.Auth.Login");

	message = std::make_shared<message::request::Auth>(login);
	return *this;
}

message::fabric::reply::Auth::Auth(bool status
	, std::string serverIP
	, unsigned short sendPort
	, unsigned short recvPort
	, long long id
	, std::string login
	, long long filter) {
	message = std::make_shared<message::reply::Auth>(status, serverIP, sendPort, recvPort, id, login, filter);
}

message::fabric::IMessageFabric& message::fabric::reply::Auth::configureFromRaw(pt::ptree data) {
	boost::optional<int> _type = data.get_optional<int>("Message.Type");
	if (!_type.has_value()) {
		throw std::invalid_argument("Type not found");
	}

	Type type = static_cast<Type>(_type.value());

	if (type != Type::auth) {
		throw std::invalid_argument("Type not coinsiding");
	}

	bool status = data.get<bool>("Message.Auth.Status");
	std::string serverIP = data.get<std::string>("Message.Auth.ServerIP");
	unsigned short sendPort = data.get<unsigned short>("Message.Auth.SendPort");
	unsigned short recvPort = data.get<unsigned short>("Message.Auth.RecvPort");
	long long id = data.get<long long>("Message.Auth.GivenId");
	std::string login = data.get<std::string>("Message.Auth.Login");
	long long filter = data.get<long long>("Message.Auth.OverallFilter");

	message = std::make_shared<message::reply::Auth>(status, serverIP, sendPort, recvPort, id, login, filter);

	return *this;
}