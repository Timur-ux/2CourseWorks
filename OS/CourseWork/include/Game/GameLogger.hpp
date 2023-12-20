#ifndef GAME_LOGGER_H_
#define GAME_LOGGER_H_
#include <sstream>

class GameLogger : public std::stringstream {
public:
	std::string str();
};


#endif // !GAME_LOGGER_H_
