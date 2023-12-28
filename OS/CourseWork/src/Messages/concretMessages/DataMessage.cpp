#include "Messages/concretMessages/DataMessage.hpp"

pt::ptree message::DataMessage::getData() {
	pt::ptree data;
	data.put<int>("Message.Type", static_cast<int>(Type::dataMessage));
	data.put<int>("Message.ReqRepType", static_cast<int>(ReqRepType::request));

	data.put<std::string>("Message.DataMessage.Data", messageData);

	return data;
}