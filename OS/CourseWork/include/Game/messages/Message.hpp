#ifndef GAME_MESSAGE_H_
#define GAME_MESSAGE_H_

#include "../visitors/MessageVisitor.hpp"

namespace game {
	namespace message {
		namespace request {
			class IMessage {
			public:
				virtual void accept(IGameMessageVisitor& visitor) = 0;
			};
		} // !game::message::request

		namespace reply {
			class IMessage {
			public:
				virtual void accept(IGameMessageVisitor& visitor) = 0;
			};
		} // !game::message::reply
	} // !game::message
} // !game

#endif // !GAME_MESSAGE_H_
