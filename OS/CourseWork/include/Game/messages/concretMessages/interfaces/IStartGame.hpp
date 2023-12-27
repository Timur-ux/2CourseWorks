#ifndef I_START_GAME_H_
#define I_START_GAME_H_

#include "Messages/Message.hpp"

namespace game {
	namespace message {
		namespace request {
			class IStartGame : public ::message::IMessage {
			public:
				virtual long long getId() = 0;
				virtual std::string getLogin() = 0;

				void accept(::message::IMessageVisitor& visitor) override {
					visitor.visit(*this);
				};
			};
		} // !game::message::request
	} // !game::message
} // !game

#endif // !I_START_GAME_H_