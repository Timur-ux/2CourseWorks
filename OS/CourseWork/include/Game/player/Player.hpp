#ifndef PLAYER_H_
#define PLAYER_H_

#include <boost/optional.hpp>
#include <string>

namespace game {
	class Player {
	private:
		long long id;
		std::string login;
		boost::optional<std::string> word = boost::none;
	public:
		Player(long long _id, std::string _login) : id(_id), login(_login) {}

		long long getId() {
			return id;
		}

		std::string getLogin() {
			return login;
		}

		void setWord(std::string _word) {
			word = _word;
		}

		boost::optional<std::string> getSelectedWord() {
			return word;
		}

		std::pair<int, int> calcCowsAndBulls(std::string otherWord);
	};

}
#endif // !PLAYER_H_
