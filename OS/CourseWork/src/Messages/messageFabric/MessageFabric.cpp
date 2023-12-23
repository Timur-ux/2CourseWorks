#include "Messages/messageFabric/MessageFabric.hpp"

using namespace message;

MessageFabric& MessageFabric::getInstance() {
	static MessageFabric instance;

	return instance;
}

message::request::IMessage MessageFabric::getRequest(request::IMessageFabric fabric) {
	return fabric.getRequest();
}

message::reply::IMessage MessageFabric::getReply(reply::IMessageFabric fabric) {
	return fabric.getReply();
}
