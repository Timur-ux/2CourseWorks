#ifndef GAME_PROCESS_CREATOR_H_
#define GAME_PROCESS_CREATOR_H_

#include "Network/ports.hpp"

#include <string>
#include <list>
#include <Windows.h>

class GameProcessCreator {
private:
	static const std::string gameApplicationName;
	static std::list<PROCESS_INFORMATION> games;
public:
	static void createNewGameProcess(std::string gameServerIP, network::PortsTriplet freePorts);
	~GameProcessCreator();
};

#endif // !GAME_PROCESS_CREATOR_H_