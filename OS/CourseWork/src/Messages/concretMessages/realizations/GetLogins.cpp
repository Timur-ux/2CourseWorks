#include "GetLogins.hpp"

pt::ptree message::request::GetLogins::getData()
{
	pt::ptree data;
	data.put<int>("Message.Type", static_cast<int>(Type::getLogins));
	data.put<int>("Message.ReqRepType", static_cast<int>(ReqRepType::request));

	data.put<long long>("Message.GetLogins.Id", id);
	data.put<std::string>("Message.GetLogins.Login", login);

	return data;
}

pt::ptree message::reply::GetLogins::getData()
{
	pt::ptree data;
	data.put<int>("Message.Type", static_cast<int>(Type::getLogins));
	data.put<int>("Message.ReqRepType", static_cast<int>(ReqRepType::reply));

	pt::ptree loginsData;
	for (auto& login : logins) {
		pt::ptree child;
		child.put("", login);
		loginsData.push_back({ "", child });
	}

	data.add_child("Message.GetLogins.Logins", loginsData);

	return data;
}
