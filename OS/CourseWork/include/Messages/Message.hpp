#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "MessageVisitor.hpp"
#include "Game/visitors/MessageVisitor.hpp"

#include <boost/property_tree/ptree.hpp>

namespace pt = boost::property_tree;

namespace message {
	class IMessage {
	public:
		virtual pt::ptree getData() = 0;

		virtual accept(request::IMessageVisitor&) {};
		virtual accept(reply::IMessageVisitor&) {};
		virtual accept(game::message::request::IGameMessageVisitor&) {};
		virtual accept(game::message::reply::IGameMessageVisitor&) {};
	};
} // !message

#endif
