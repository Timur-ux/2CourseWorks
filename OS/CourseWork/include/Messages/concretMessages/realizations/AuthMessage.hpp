#ifndef AUTH_MESSAGE_H_
#define AUTH_MESSAGE_H_
#include "../interfaces/IAuthMessage.hpp"

namespace message {
	namespace request {
		class Auth : public IAuth {
		private:
			std::string login;
			pt::ptree data;
		public:
			Auth(std::string _login) : login(_login) {}

			std::string getLogin() override {
				return login;
			}

			pt::ptree getData() override;
		};
	} // !message::request

	namespace reply {
		class Auth : public IAuth {
		private:
			pt::ptree data;
			
			bool authStatus;
			std::string serverIP;
			unsigned short sendPort;
			unsigned short recvPort;
			long long givenId;
			std::string login;
			long long overallFilter;
		public:
			Auth(
				bool _authStatus
				, std::string _serverIP
				, unsigned short _sendPort
				, unsigned short _recvPort
				, long long _givenId
				, std::string _login
				, long long _overallFilter) 
				: authStatus(_authStatus)
				, serverIP(_serverIP)
				, sendPort(_sendPort)
				, recvPort(_recvPort)
				, givenId(_givenId)
				, login(_login)
				, overallFilter(_overallFilter) {}

			bool getAuthStatus() override {
				return authStatus;
			}

			std::string getServerIP() override {
				return serverIP;
			}

			unsigned short getSendPort() override {
				return sendPort;
			}

			unsigned short getRecvPort() override {
				return recvPort;
			}

			long long getGivenId() override {
				return givenId;
			}

			std::string getLogin() override {
				return login;
			}

			long long getOverallFilter() override {
				return overallFilter;
			}

			pt::ptree getData() override;
		};
	}
} // !message

#endif // !AUTH_MESSAGE_H_