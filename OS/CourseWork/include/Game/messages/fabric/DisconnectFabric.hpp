#ifndef DISCONNECT_MESSAGE_FABRIC_H_
#define DISCONNECT_MESSAGE_FABRIC_H_

#include "Messages/messageFabric/ConcretFabric/IMessageFabric.hpp"

#include <string>

namespace game {
	namespace message {
		namespace fabric {
			namespace request {
				class Disconnect : public ::message::fabric::IMessageFabric {
				public:
					Disconnect(pt::ptree data) {
						configureFromRaw(data);
					}

					Disconnect(long long id, std::string login);

					::message::fabric::IMessageFabric& configureFromRaw(pt::ptree) override;
					std::shared_ptr<::message::IMessage> getMessage() override;
				};
			} // !game::message::fabric::request
		} // !game::message::fabric
	} // !game::message
} // !game

#endif // !DISCONNECT_MESSAGE_FABRIC_H_