#ifndef CREATE_NEW_GAME_MESSAGE_H_
#define CREATE_NEW_GAME_MESSAGE_H_

#include "../interfaces/ICreateNewGame.hpp"

namespace message {
	namespace request {
		class CreateNewGame : public ICreateNewGame {
		private:
			long long id;
			std::string login;
			std::list<std::string> logins;
		public:
			CreateNewGame(long long _id, std::string _login, std::list<std::string> _logins) : id(_id), login(_login), logins(_logins) {}
			
			long long getId() override {
				return id;
			}

			std::string getLogin() {
				return login;
			}

			std::list<std::string> getLogins() override {
				return logins;
			}

			pt::ptree getData() override;
		};
	}
}

#endif // !CREATE_NEW_GAME_MESSAGE_H_