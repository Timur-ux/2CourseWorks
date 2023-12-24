#ifndef GET_LOGINS_MESSAGE_FABRIC_H_
#define GET_LOGINS_MESSAGE_FABRIC_H_

#include "IMessageFabric.hpp"
#include "../../concretMessages/interfaces/IGetLogins.hpp"

#include <list>

namespace message {
	namespace fabric {
		namespace request {
			class GetLogins : public IMessageFabric {
			public:
				GetLogins(std::string login, long long id);

				message::request::IMessage getMessage() override;
			};
		} // !message::fabric::request

		namespace reply {
			class GetLogins : public IMessageFabric {
			public:
				GetLogins(std::list<std::string> logins);

				message::reply::IMessage getMessage() override;
			};
		} // !message::fabric::reply
	} // !message::fabric

} // !message


#endif // !GET_LOGINS_MESSAGE_FABRIC_H_