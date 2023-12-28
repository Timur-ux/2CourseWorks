#include "../interfaces/ISelectWord.hpp"

namespace game {
	namespace message {
		namespace request {
			class SelectWord : public ISelectWord {
			public:
				pt::ptree getData() override;
			};
		}

		namespace reply {
			class SelectWord : public ISelectWord {
			private:
				long long id;
				std::string login;
				std::string word;
			public:
				SelectWord(long long _id, std::string _login, std::string _word)
					: id(_id)
					, login(_login)
					, word(_word) {}

				long long getId() override {
					return id;
				}
				
				std::string getLogin() override {
					return login;
				}

				std::string getWord() override {
					return word;
				}

				pt::ptree getData() override;
			};
		}
	}
}