#ifndef CREATE_NEW_GAME_MESSAGE_FABRIC_H_
#define CREATE_NEW_GAME_MESSAGE_FABRIC_H_

#include "IMessageFabric.hpp"
#include "../../concretMessages/interfaces/ICreateNewGame.hpp"

#include <list>

namespace message {
	namespace fabric {
		namespace request {
			class CreateNewGame : public IMessageFabric {
			public:
				CreateNewGame(std::list<std::string> logins);

				message::request::IMessage getMessage() override;
			};
		} // !message::fabric::request

		namespace reply {
			class CreateNewGame : public IMessageFabric {
			public:
				CreateNewGame();

				message::reply::IMessage getMessage() override;
			};
		} // !message::fabric::reply
	} // !message::fabric
	
}

#endif // !CREATE_NEW_GAME_MESSAGE_FABRIC_H_
