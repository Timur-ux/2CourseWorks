#ifndef MESSAGE_FABRIC_H_
#define MESSAGE_FABRIC_H_

#include "ConcretFabric/IMessageFabric.hpp"
#include "ConcretFabric/AuthMessageFabric.hpp"
#include "ConcretFabric/CreateNewGameFabric.hpp"
#include "ConcretFabric/GetLoginsMessageFabric.hpp"
#include "ConcretFabric/PingMessageFabric.hpp"
#include "ConcretFabric/InviteToGameFabric.hpp"
#include "Game/messages/fabric/SelectWordFabric.hpp"
#include "Game/messages/fabric/GuessWordFabric.hpp"

#include <boost/optional.hpp>
#include <boost/property_tree/ptree.hpp>
#include <memory>

namespace pt = boost::property_tree;

namespace message {
	namespace fabric {
		class MessageFabric {
		private:
			MessageFabric() = default;
		public:
			static MessageFabric& getInstance();
			std::shared_ptr<IMessage> getRequest(request::IMessageFabric&& fabric);
			std::shared_ptr<IMessage> getReply(reply::IMessageFabric&& fabric);
			boost::optional<std::shared_ptr<IMessage>> getFromRawData(pt::ptree data);
		};
	}
}

#endif // !MESSAGE_FABRIC_H_