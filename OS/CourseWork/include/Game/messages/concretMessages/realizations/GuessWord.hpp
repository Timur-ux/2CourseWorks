#ifndef GUESS_WORD_MESSAGE_H_
#define GUESS_WORD_MESSAGE_H_

#include "../interfaces/IGuessWord.hpp"

namespace game {
	namespace message {
		namespace request {
			class GuessWord : public IGuessWord {
			public:
				pt::ptree getData() override;
			};
		}

		namespace reply {
			class GuessWord : public IGuessWord {
			private:
				long long id;
				std::string login;
				std::string word;
				std::string opponent;
			public:
				GuessWord(long long _id, std::string _login, std::string _word, std::string _opponent)
					: id(_id)
					, login(_login)
					, word(_word)
					, opponent(_opponent) {}

				long long getId() override {
					return id;
				}

				std::string getLogin() override {
					return login;
				}

				std::string getWord() override {
					return word;
				}

				std::string getOpponent() override {
					return opponent;
				}

				pt::ptree getData() override;
			};
		}
	}
}
#endif // !GUESS_WORD_MESSAGE_H_