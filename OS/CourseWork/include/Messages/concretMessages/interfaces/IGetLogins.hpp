#ifndef I_GET_LOGINS_H_
#define I_GET_LOGINS_H_

#include "../../Message.hpp"
#include <string>
#include <list>

namespace message {
	namespace request {
		class IGetLogins : public IMessage {
		public:
			virtual std::string getLogin() = 0;
			virtual long long getId() = 0;
			virtual void accept(IMessageVisitor& visitor) {
				visitor.visit(*this);
			}
		};
	} // !request

	namespace reply {
		class IGetLogins : public IMessage {
		public:
			virtual std::list<std::string> getLogins() = 0;
			virtual void setLogins(std::list<std::string>) = 0;

			virtual void accept(IMessageVisitor& visitor) {
				visitor.visit(*this);
			}
		};
	} // !request
}


#endif // !I_GET_LOGINS
