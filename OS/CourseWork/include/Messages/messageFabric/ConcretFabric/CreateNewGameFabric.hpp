#ifndef CREATE_NEW_GAME_MESSAGE_FABRIC_H_
#define CREATE_NEW_GAME_MESSAGE_FABRIC_H_

#include "IMessageFabric.hpp"
#include "../../concretMessages/interfaces/ICreateNewGame.hpp"

#include <list>

namespace message {
	namespace fabric {
		namespace request {
			class CreateNewGame : public IMessageFabric {
			private:
				std::shared_ptr<IMessage> message;
			public:
				CreateNewGame(pt::ptree data) {
					configureFromRaw(data);
				}

				CreateNewGame(std::list<std::string> logins);

				IMessageFabric& configureFromRaw(pt::ptree) override;
				std::shared_ptr<IMessage> getMessage() override {
					return message;
				}
			};
		} // !message::fabric::request
	} // !message::fabric
	
}

#endif // !CREATE_NEW_GAME_MESSAGE_FABRIC_H_
