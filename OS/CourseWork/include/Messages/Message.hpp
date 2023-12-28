#ifndef MESSAGE_H_
#define MESSAGE_H_


#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "MessageVisitor.hpp"
#include "MessageTypes.hpp"
#include "Game/messages/GameMessageTypes.hpp"

namespace pt = boost::property_tree;

namespace message {
	class IMessage {
	public:
		virtual pt::ptree getData() = 0;

		virtual void accept(IMessageVisitor&) = 0;
	};
} // !message

#endif
