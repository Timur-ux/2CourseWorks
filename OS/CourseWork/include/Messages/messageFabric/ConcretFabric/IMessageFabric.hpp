#ifndef I_MESSAGE_FABRIC_H_
#define I_MESSAGE_FABRIC_H_

#include "../Message.hpp"
#include <string>

namespace message {
	namespace fabric {
		namespace request {
			class IMessageFabric {
			public:
				virtual message::request::IMessage getMessage() = 0;
			};
		} // !message::fabric::request

		namespace reply {
			class IMessageFabric {
			public:
				virtual message::reply::IMessage getMessage() = 0;
			};
		} // !message::fabric::reply
	}
	
} // !message
#endif // !I_MESSAGE_FABRIC_H_
