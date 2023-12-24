#ifndef I_GUESS_WORD_H_
#define I_GUESS_WORD_H_

#include "Messages/Message.hpp"
#include "Game/visitors/MessageVisitor.hpp"

#include <string>

namespace game {
	namespace message {
		namespace request {
			class IDisconnect : public ::message::IMessage {
			public:
				virtual std::string getLogin() = 0;
				virtual long long getId() = 0;

				void accept(IGameMessageVisitor& visitor) override {
					visitor.visit(*this);
				};
			};
		} // !game::message::request
	} // !game::message
} // !game

#endif // !I_GUESS_WORD_H_