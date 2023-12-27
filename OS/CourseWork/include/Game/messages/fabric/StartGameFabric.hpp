#ifndef START_GAME_MESSAGE_FABRIC_H_
#define START_GAME_MESSAGE_FABRIC_H_

#include "Messages/messageFabric/ConcretFabric/IMessageFabric.hpp"

#include <string>

namespace game {
	namespace message {
		namespace fabric {
			namespace request {
				class StartGame : public ::message::fabric::IMessageFabric {
				public:
					StartGame(pt::ptree data) {
						configureFromRaw(data);
					}

					StartGame(long long id, std::string login);

					::message::fabric::IMessageFabric& configureFromRaw(pt::ptree) override;
					std::shared_ptr<::message::IMessage> getMessage() override;
				};
			} // !game::message::fabric::request
		} // !game::message::fabric
	} // !game::message
} // !game

#endif // !START_GAME_MESSAGE_FABRIC_H_
