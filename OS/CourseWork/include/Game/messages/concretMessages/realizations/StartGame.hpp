#ifndef START_GAME_MESSAGE_H_
#define START_GAME_MESSAGE_H_

#include "../interfaces/IStartGame.hpp"

#include <string>

namespace game {
	namespace message {
		namespace request {
			class StartGame : public IStartGame {
				long long id;
				std::string login;
			public:
				StartGame(long long _id, std::string _login)
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

#endif // !START_GAME_MESSAGE_H_