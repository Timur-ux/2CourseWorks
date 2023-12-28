#include "Messages/concretMessages/realizations/InviteToGame.hpp"

pt::ptree message::reply::InviteToGame::getData()
{
	pt::ptree data;
	data.put<int>("Message.Type", static_cast<int>(Type::getLogins));
	data.put<int>("Message.ReqRepType", static_cast<int>(ReqRepType::reply));

	data.put<std::string>("Message.InviteToGame.ServerIP", serverIP);
	data.put<unsigned short>("Message.InviteToGame.AuthPort", authPort);

	return data;
}