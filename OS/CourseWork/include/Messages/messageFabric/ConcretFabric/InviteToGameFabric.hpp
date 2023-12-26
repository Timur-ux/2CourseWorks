#ifndef INVITE_TO_GAME_FABRIC_H_
#define INVITE_TO_GAME_FABRIC_H_

#include "IMessageFabric.hpp"
#include "../../concretMessages/interfaces/IInviteToGame.hpp"

#include <string>

namespace message {
	namespace fabric {
		namespace reply {
			class InviteToGame : public IMessageFabric {
			public:
				InviteToGame(pt::ptree data) {
					configureFromRaw(data);
				}

				InviteToGame(std::string gameServerIP, unsigned short gameServerAuthPort);

				IMessageFabric& configureFromRaw(pt::ptree) override;
				std::shared_ptr<IMessage> getMessage() override;
			};
		} // !message::fabric::reply
	} // !message::fabric
} // !message

#endif // !INVITE_TO_GAME_FABRIC_H_
