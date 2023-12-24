#ifndef I_SELECT_WORD_H_
#define I_SELECT_WORD_H_

#include "Messages/Message.hpp"

#include <string>

namespace game {
	namespace message {
		namespace request {
			class ISelectWord : public ::message::IMessage {
			public:
				void accept(::message::IMessageVisitor& visitor) override {
					visitor.visit(*this);
				};
			};
		} // !game::message::request

		namespace reply {
			class ISelectWord : public ::message::IMessage {
			public:
				virtual long long getId() = 0;
				virtual std::string getLogin() = 0;
				virtual std::string getWord() = 0;

				void accept(::message::IMessageVisitor& visitor) override {
					visitor.visit(*this);
				};
			};
		} // !game::message::reply
	} // !game::message
} // !game

#endif // !I_SELECT_WORD_H_