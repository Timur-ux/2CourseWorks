#ifndef GET_LOGINS_MESSAGE_H_
#define GET_LOGINS_MESSAGE_H_
#include "../interfaces/IGetLogins.hpp"

namespace message {
	namespace request {
		class GetLogins : public IGetLogins {
		private:
			std::string login;
			long long id;
			pt::ptree data;
		public:
			GetLogins(long long _id, std::string _login) : id(_id), login(_login) {};

			std::string getLogin() override {
				return login;
			}

			long long getId() override {
				return id;
			}

			pt::ptree getData() override;
		};
	} // !message::request

	namespace reply {
		class GetLogins : public IGetLogins {
		private:
			std::list<std::string> logins;
			pt::ptree data;
		public:
			GetLogins(std::list<std::string> _logins) : logins(_logins) {};

			std::string getLogins() override {
				return logins;
			}

			pt::ptree getData() override;
		};
	}
} // !message

#endif // !GET_LOGINS_MESSAGE_H_