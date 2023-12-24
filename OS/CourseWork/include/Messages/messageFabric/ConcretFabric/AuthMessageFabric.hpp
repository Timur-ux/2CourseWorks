#ifndef AUTH_MESSAGE_FABRIC_H_
#define AUTH_MESSAGE_FABRIC_H_

#include "IMessageFabric.hpp"
#include "../../concretMessages/interfaces/IAuthMessage.hpp"

namespace message {
	namespace fabric {
		namespace request {
			class Auth : public IMessageFabric {
			public:
				Auth(std::string login);

				message::request::IMessage getMessage() override;
			};
		} // !message::fabric::request

		namespace reply {
			class Auth : public IMessageFabric {
			public:
				Auth(bool status
					, std::string serverIP
					, unsigned short sendPort
					, unsigned short recvPort
					, long long givenId
					, std::string acceptedLogin);

				message::reply::IMessage getMessage() override;
			};
		} // !message::fabric::request
	}
}

#endif // !AUTH_MESSAGE_FABRIC_H_