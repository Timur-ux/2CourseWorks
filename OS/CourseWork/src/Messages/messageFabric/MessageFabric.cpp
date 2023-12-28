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
	ReqRepType reqRep = static_cast<ReqRepType>(_reqRep.value());
	
	std::string message;
	game::message::Type gameActionType;
	try {
		switch (type) {
		case Type::auth:
			if (reqRep == ReqRepType::request) return request::Auth(data).getMessage();
			if (reqRep == ReqRepType::reply) return reply::Auth(data).getMessage();
			break;
		case Type::createNewGame:
			if (reqRep == ReqRepType::request) return request::CreateNewGame(data).getMessage();
			break;
		case Type::getLogins:
			if (reqRep == ReqRepType::request) return request::GetLogins(data).getMessage();
			if (reqRep == ReqRepType::reply) return reply::GetLogins(data).getMessage();
		case Type::dataMessage:
			 message = data.get<std::string>("Message.DataMessage.Data");
			return static_cast<std::shared_ptr<IMessage>>(std::make_shared<DataMessage>(message));
		case Type::gameAction:
			gameActionType = static_cast<game::message::Type>(data.get<int>("Message.GameAction"));
			
			switch (gameActionType) {
			case game::message::Type::disconnect:
				return game::message::fabric::request::Disconnect(data).getMessage();
			case game::message::Type::guessWord:
				if (reqRep == message::ReqRepType::request) return game::message::fabric::request::GuessWord(data).getMessage();
				if(reqRep == message::ReqRepType::request) return game::message::fabric::reply::GuessWord(data).getMessage();
			case game::message::Type::selectWord:
				if (reqRep == message::ReqRepType::request) return game::message::fabric::request::SelectWord(data).getMessage();
				if (reqRep == message::ReqRepType::request) return game::message::fabric::reply::SelectWord(data).getMessage();
			case game::message::Type::startGame:
				return game::message::fabric::request::StartGame(data).getMessage();
			}
			break;
		case Type::inviteToGame:
			return message::fabric::reply::InviteToGame(data).getMessage();
		case Type::ping:
			if (reqRep == message::ReqRepType::request) return message::fabric::request::Ping(data).getMessage();
			if (reqRep == message::ReqRepType::request) return message::fabric::reply::Ping(data).getMessage();
		}

	}
	catch (std::exception& e) {
		printErr() << e.what() << std::endl;
	}

	return boost::none;
}
