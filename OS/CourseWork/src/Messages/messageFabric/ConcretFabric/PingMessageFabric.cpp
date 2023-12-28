#include "Messages/messageFabric/ConcretFabric/PingMessageFabric.hpp"
#include "Messages/concretMessages/realizations/PingMessage.hpp"

message::fabric::request::Ping::Ping() {
	message = std::make_shared<message::request::Ping>();
}

message::fabric::IMessageFabric& message::fabric::request::Ping::configureFromRaw(pt::ptree data) {
	boost::optional<int> _type = data.get_optional<int>("Message.Type");
	if (!_type.has_value()) {
		throw std::invalid_argument("Type not found");
	}

	Type type = static_cast<Type>(_type.value());

	if (type != Type::ping) {
		throw std::invalid_argument("Type not coinsiding");
	}

	message = std::make_shared<message::request::Ping>();
	return *this;
}

message::fabric::reply::Ping::Ping(long long id, std::string login) {
	message = std::make_shared<message::reply::Ping>(id, login);
}

message::fabric::IMessageFabric& message::fabric::reply::Ping::configureFromRaw(pt::ptree data) {
	boost::optional<int> _type = data.get_optional<int>("Message.Type");
	if (!_type.has_value()) {
		throw std::invalid_argument("Type not found");
	}

	Type type = static_cast<Type>(_type.value());

	if (type != Type::ping) {
		throw std::invalid_argument("Type not coinsiding");
	}

	long long id = data.get<long long>("Message.Ping.Id");
	std::string login = data.get<std::string>("Message.Ping.Login");

	message = std::make_shared<message::reply::Ping>(id, login);
	return *this;
}