#ifndef I_DISCONNECT_H_
#define I_DISCONNECT_H_

#include "Messages/Message.hpp"

#include <string>

namespace game {
	namespace message {
		namespace request {
			class IDisconnect : public ::message::IMessage {
			public:
				virtual std::string getLogin() = 0;
				virtual long long getId() = 0;

				pt::ptree getData() override;

				void accept(::message::IMessageVisitor& visitor) override {
					visitor.visit(*this);
				};
			};
		} // !game::message::request
	} // !game::message
} // !game

#endif // !I_DISCONNECT_H_