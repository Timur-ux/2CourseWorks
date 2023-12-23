#ifndef I_PING_MESSAGE_H_
#define I_PING_MESSAGE_H_

#include "../../Message.hpp"

#include <string>

namespace message {
	namespace request {
		class IPing : public IMessage {
		public:
			virtual void accept(IMessageVisitor & visitor) {
				visitor.visit(*this);
			}

		};
	} // !request

	namespace reply {
		class IPing : public IMessage {
		public:
			virtual std::string getLogin() = 0;
			virtual long long getId() = 0;

			virtual void accept(IMessageVisitor& visitor) {
				visitor.visit(*this);
			}
		};
	} // !reply
}


#endif // !I_PING_MESSAGE_H_
