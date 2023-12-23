#ifndef I_CREATE_NEW_GAME_H_
#define I_CREATE_NEW_GAME_H_

#include "../../Message.hpp"
#include <string>
#include <list>

namespace message {
	namespace request {
		class ICreateNewGame : public IMessage {
		public:
			std::list<std::string> getLogins() = 0;

			virtual void accept(IMessageVisitor& visitor) {
				visitor.visit(*this);
			}
		};
	} // !request

	namespace reply {
		class ICreateNewGame : public IMessage {
		public:
			virtual void accept(IMessageVisitor& visitor) {
				visitor.visit(*this);
			}
		};
	} // !request
}


#endif // !I_GET_LOGINS
