#include "Messages/concretMessages/realizations/AuthMessage.hpp"

namespace message {
	namespace request {
		pt::ptree Auth::getData()
		{
			pt::ptree data;
			data.put<int>("Message.Type", static_cast<int>(Type::auth));
			data.put<int>("Message.ReqRepType", static_cast<int>(ReqRepType::request));

			data.put<std::string>("Message.Auth.Login", login);

			return data;
		}
	} // !message::request

	namespace reply {
		pt::ptree Auth::getData()
		{
			pt::ptree data;
			data.put<int>("Message.Type", static_cast<int>(Type::auth));
			data.put<int>("Message.ReqRepType", static_cast<int>(ReqRepType::reply));

			data.put("Message.Auth.Status", authStatus);
			data.put("Message.Auth.ServerIP", serverIP);
			data.put("Message.Auth.SendPort", sendPort);
			data.put("Message.Auth.RecvPort", recvPort);
			data.put("Message.Auth.GivenId", givenId);
			data.put("Message.Auth.Login", login);
			data.put("Message.Auth.OverallFilter", overallFilter);

			return data;
		}
	} // !message::reply
} // !message
