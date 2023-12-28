#ifndef INVITE_TO_GAME_MESSAGE_H_
#define INVITE_TO_GAME_MESSAGE_H_
#include "../interfaces/IInviteToGame.hpp"

#include <string>

namespace message {
	namespace reply {
		class InviteToGame : public IInviteToGame {
		private:
			std::string serverIP;
			unsigned short authPort;
			pt::ptree data;
		public:
			InviteToGame(std::string _serverIP, unsigned short _authPort)
				: serverIP(_serverIP), authPort(_authPort) {};

			std::string getGameServerIP() override {
				return serverIP;
			}

			unsigned short getGameServerAuthPort() override {
				return authPort;
			}

			pt::ptree getData() override;
		};
	} // !message::request
} // !message

#endif // !INVITE_TO_GAME_MESSAGE_H_