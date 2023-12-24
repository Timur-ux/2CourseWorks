#ifndef I_AUTH_MESSAGE_H_
#define I_AUTH_MESSAGE_H_

#include "../../Message.hpp"

#include <string>

namespace message {
	namespace request {
		class IAuth : public IMessage {
		public:
			virtual std::string getLogin() = 0;

			virtual void accept(IMessageVisitor& visitor) override {
				visitor.visit(*this);
			}
		};
	} // !request

	namespace reply {
		class IAuth : public IMessage {
		public:
			virtual bool getAuthStatus() = 0;
			virtual std::string getServerIP() = 0;
			virtual unsigned short getSendPort() = 0;
			virtual unsigned short getRecvPort() = 0;
			virtual long long getGivenId() = 0;
			virtual std::string getLogin() = 0;
			virtual long long getOverallFilter() = 0;

			virtual void accept(IMessageVisitor& visitor) {
				visitor.visit(*this);
			}
		};
	} // !reply
}


#endif // !I_AUTH_MESSAGE_H_
