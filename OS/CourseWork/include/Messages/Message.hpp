#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "MessageVisitor.hpp"

namespace message {
	namespace request {
		class IMessage {
		public:
			virtual accept(IMessageVisitor& visitor) = 0;
		};
	} // !message::request

	namespace reply {
		class IMessage {
		public:
			virtual accept(IMessageVisitor& visitor) = 0;
		};
	}
} // !message

#endif
