#ifndef I_INVITE_TO_GAME_MESSAGE_H_
#define I_INVITE_TO_GAME_MESSAGE_H_

#include "../../Message.hpp"

namespace message {
	namespace reply {
		class IInviteToGame : public IMessage {
		public:
			virtual std::string getGameServerIP() = 0;
			virtual unsigned short getGameServerAuthPort() = 0;

			virtual void accept(IMessageVisitor& visitor) {
				visitor.visit(*this);
			}
		};

	} // !message::reply
} // !message

#endif // !I_INVITE_TO_GAME_MESSAGE_H_
