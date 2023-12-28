#ifndef DISCONNECT_MESSAGE_H_
#define DISCONNECT_MESSAGE_H_

#include "../interfaces/IDisconnect.hpp"

#include <string>

namespace game {
	namespace message {
		namespace request {
			class Disconnect : public IDisconnect {
				long long id;
				std::string login;
			public:
				Disconnect(long long _id, std::string _login)
					: id(_id), login(_login) {}

				long long getId() override {
					return id;
				}

				std::string getLogin() override {
					return login;
				}

				pt::ptree getData() override;
			};
		}
	}
}

#endif // !DISCONNECT_MESSAGE_H_