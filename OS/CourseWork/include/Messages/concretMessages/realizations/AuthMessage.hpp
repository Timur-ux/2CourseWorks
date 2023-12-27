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
} // !message