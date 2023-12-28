#ifndef CREATE_NEW_GAME_MESSAGE_H_
#define CREATE_NEW_GAME_MESSAGE_H_

#include "../interfaces/ICreateNewGame.hpp"

namespace message {
	namespace request {
		class CreateNewGame : public ICreateNewGame {
		private:
			std::list<std::string> logins;
		public:
			CreateNewGame(std::list<std::string> _logins) : logins(_logins) {}
			std::list<std::string> getLogins() override {
				return logins;
			}

			pt::ptree getData() override;
		};
	}
}

#endif // !CREATE_NEW_GAME_MESSAGE_H_