#include "Game/GameLogger.hpp"


std::string GameLogger::str() {
	return "[Game] " + std::stringstream::str();
}