#include "Messages/messageFabric/MessageFabric.hpp"
#include "print.hpp"

using namespace message::fabric;

MessageFabric& MessageFabric::getInstance() {
	static MessageFabric instance;

	return instance;
}

std::shared_ptr<message::IMessage> MessageFabric::getRequest(IMessageFabric&& fabric) {
	return fabric.getMessage();
}

std::shared_ptr<message::IMessage> MessageFabric::getReply(IMessageFabric&& fabric) {
	return fabric.getMessage();
}

boost::optional<std::shared_ptr<message::IMessage>> message::fabric::MessageFabric::getFromRawData(pt::ptree data)
{
	boost::optional<int> _type = data.get_optional<int>("Message.Type");
	boost::optional<int> _reqRep = data.get_optional<int>("Message.ReqRepType");
	if (!_type.has_value() || !_reqRep.has_value()) {
		return boost::none;
	}

	Type type = static_cast<Type>(_type.value());
	ReqRepType reqReq = static_cast<ReqRepType>(_reqRep.value());

	try {
		switch (type) {
		case Type::auth:
			if (reqReq == ReqRepType::request) return request::Auth(data).getMessage();
			if (reqReq == ReqRepType::reply) return reply::Auth(data).getMessage();
			break;
		case Type::createNewGame:
			if (reqReq == ReqRepType::request) return request::CreateNewGame(data).getMessage();
			break;
		case Type::getLogins:
			if (reqReq == ReqRepType::request) return request::GetLogins(data).getMessage();
			if (reqReq == ReqRepType::reply) return reply::GetLogins(data).getMessage();
		}
	}
	catch (std::exception& e) {
		printErr() << e.what() << std::endl;
	}

	return boost::none;
}
