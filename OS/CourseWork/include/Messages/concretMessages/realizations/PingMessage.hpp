#ifndef	PING_MESSAGE_H_
#define PING_MESSAGE_H_
#include "../interfaces/IPingMessage.hpp"

namespace message {
	namespace request {
		class Ping : public IPing {
		private:
			pt::ptree data;
		public:
			pt::ptree getData() override;
		};
	} // !message::request

	namespace reply {
		class Ping : public IPing {
		private:
			std::string login;
			long long id;
			pt::ptree data;
		public:
			Ping(long long _id, std::string _login) : id(_id), login(_login) {};

			std::string getLogin() override {
				return login;
			}

			long long getId() override {
				return id;
			}

			pt::ptree getData() override;
		};
	}
} // !message

#endif // !PING_MESSAGE_H_