#ifndef PING_MESSAGE_FABRIC_H_
#define PING_MESSAGE_FABRIC_H_

#include "IMessageFabric.hpp"
#include "../../concretMessages/interfaces/IPingMessage.hpp"

namespace message {
	namespace fabric {
		namespace request {
			class Ping : public IMessageFabric {
			public:
				Ping();

				std::shared_ptr<IMessage> getMessage() override;
			};
		} // !message::fabric::request

		namespace reply {
			class Ping : public IMessageFabric {
			public:
				Ping(long long id, std::string login);

				std::shared_ptr<IMessage> getMessage() override;
			};
		} // !message::fabric::reply
	} // !message::fabric

} // !message

#endif // !PING_MESSAGE_FABRIC_H_