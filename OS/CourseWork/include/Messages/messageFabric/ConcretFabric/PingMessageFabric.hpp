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

				IMessageFabric& configureFromRaw(pt::ptree) override;
				std::shared_ptr<IMessage> getMessage() override;
			};
		} // !message::fabric::request

		namespace reply {
			class Ping : public IMessageFabric {
			public:
				Ping(pt::ptree data) {
					configureFromRaw(data);
				}
				Ping(long long id, std::string login);

				IMessageFabric& configureFromRaw(pt::ptree) override;
				std::shared_ptr<IMessage> getMessage() override;
			};
		} // !message::fabric::reply
	} // !message::fabric

} // !message

#endif // !PING_MESSAGE_FABRIC_H_