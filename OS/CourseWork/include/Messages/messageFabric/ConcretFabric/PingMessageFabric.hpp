#ifndef PING_MESSAGE_FABRIC_H_
#define PING_MESSAGE_FABRIC_H_

#include "IMessageFabric.hpp"

namespace message {
	namespace fabric {
		namespace request {
			class Ping : public IMessageFabric {
			public:
				Ping();

				message::request::IMessage getMessage() override;
			};
		} // !message::fabric::request

		namespace reply {
			class Ping : public IMessageFabric {
			public:
				Ping(std::string login, long long id);

				message::reply::IMessage getMessage() override;
			};
		} // !message::fabric::reply
	} // !message::fabric

} // !message

#endif // !PING_MESSAGE_FABRIC_H_