#ifndef I_START_GAME_H_
#define I_START_GAME_H_

#include "Messages/Message.hpp"
#include "Game/visitors/MessageVisitor.hpp"

namespace game {
	namespace message {
		namespace request {
			class IStartGame : public ::message::IMessage {
			public:
				void accept(IGameMessageVisitor& visitor) override {
					visitor.visit(*this);
				};
			};
		} // !game::message::request
	} // !game::message
} // !game

#endif // !I_START_GAME_H_