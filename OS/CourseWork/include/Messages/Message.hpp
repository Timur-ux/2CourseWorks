#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "MessageVisitor.hpp"
#include "Game/visitors/MessageVisitor.hpp"

#include <boost/property_tree/ptree.hpp>
#include <concepts>
#include <type_traits>

namespace pt = boost::property_tree;

namespace message {
	class IMessage;

	class IMessage {
	public:
		virtual pt::ptree getData() = 0;

		virtual void accept(request::IMessageVisitor&) {};
		virtual void accept(reply::IMessageVisitor&) {};
		virtual void accept(game::message::request::IGameMessageVisitor&) {};
		virtual void accept(game::message::reply::IGameMessageVisitor&) {};
	};
} // !message

#endif
