#ifndef MESSAGE_FABRIC_H_
#define MESSAGE_FABRIC_H_

#include "ConcretFabric/IMessageFabric.hpp"
#include "ConcretFabric/AuthMessageFabric.hpp"
#include "ConcretFabric/CreateNewGameFabric.hpp"
#include "ConcretFabric/GetLoginsMessageFabric.hpp"
#include "ConcretFabric/PingMessageFabric.hpp"

namespace message {
	namespace fabric {
		class MessageFabric {
		private:
			MessageFabric() = default;
		public:
			static MessageFabric& getInstance();
			message::request::IMessage getRequest(request::IMessageFabric fabric);
			message::reply::IMessage getReply(reply::IMessageFabric fabric);
		};
	}
}

#endif // !MESSAGE_FABRIC_H_