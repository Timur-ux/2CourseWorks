#ifndef AUTH_MESSAGE_FABRIC_H_
#define AUTH_MESSAGE_FABRIC_H_

#include "IMessageFabric.hpp"
#include "../../concretMessages/interfaces/IAuthMessage.hpp"

namespace message {
	namespace fabric {
		namespace request {
			class Auth : public IMessageFabric {
			public:
				Auth(pt::ptree data) {
					configureFromRaw(data);
				}

				Auth(std::string login);

				IMessageFabric& configureFromRaw(pt::ptree) override;
				std::shared_ptr<IMessage> getMessage() override;
			};
		} // !message::fabric::request

		namespace reply {
			class Auth : public IMessageFabric {
			public:
				Auth(pt::ptree data) {
					configureFromRaw(data);
				}

				Auth(bool status
					, std::string serverIP
					, unsigned short sendPort
					, unsigned short recvPort
					, long long givenId
					, std::string acceptedLogin
					, long long overallFilter);

				IMessageFabric& configureFromRaw(pt::ptree) override;
				std::shared_ptr<IMessage> getMessage() override;
			};
		} // !message::fabric::request
	}
}

#endif // !AUTH_MESSAGE_FABRIC_H_