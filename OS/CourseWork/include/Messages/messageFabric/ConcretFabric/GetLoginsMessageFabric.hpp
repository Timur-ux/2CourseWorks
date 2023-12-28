#ifndef GET_LOGINS_MESSAGE_FABRIC_H_
#define GET_LOGINS_MESSAGE_FABRIC_H_

#include "IMessageFabric.hpp"
#include "../../concretMessages/interfaces/IGetLogins.hpp"

#include <list>

namespace message {
	namespace fabric {
		namespace request {
			class GetLogins : public IMessageFabric {
			private:
					std::shared_ptr<IMessage> message;
			public:
				GetLogins(pt::ptree data) {
					configureFromRaw(data);
				}

				GetLogins(std::string login, long long id);

				IMessageFabric& configureFromRaw(pt::ptree) override;
				std::shared_ptr<IMessage> getMessage() override {
					return message;
				}
			};
		} // !message::fabric::request

		namespace reply {
			class GetLogins : public IMessageFabric {
			private:
					std::shared_ptr<IMessage> message;
			public:
				GetLogins(pt::ptree data) {
					configureFromRaw(data);
				}

				GetLogins(std::list<std::string> logins);

				IMessageFabric& configureFromRaw(pt::ptree) override;
				std::shared_ptr<IMessage> getMessage() override {
					return message;
				}
			};
		} // !message::fabric::reply
	} // !message::fabric

} // !message


#endif // !GET_LOGINS_MESSAGE_FABRIC_H_