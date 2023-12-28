#include "Messages/concretMessages/realizations/PingMessage.hpp"

pt::ptree message::request::Ping::getData() {
	pt::ptree data;
	data.put<int>("Message.Type", static_cast<int>(Type::getLogins));
	data.put<int>("Message.ReqRepType", static_cast<int>(ReqRepType::request));

	return data;
}

pt::ptree message::reply::Ping::getData() {
	pt::ptree data;
	data.put<int>("Message.Type", static_cast<int>(Type::getLogins));
	data.put<int>("Message.ReqRepType", static_cast<int>(ReqRepType::reply));

	data.put<long long>("Message.Ping.Id", id);
	data.put<std::string>("Message.Ping.Login", login);

	return data;
}