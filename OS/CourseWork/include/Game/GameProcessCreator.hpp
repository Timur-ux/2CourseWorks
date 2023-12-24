#ifndef GAME_PROCESS_CREATOR_H_
#define GAME_PROCESS_CREATOR_H_

#include "Network/ports.hpp"

#include <string>
#include <Windows.h>

class GameProcessCreator {
private:
	static std::string gameApplicationName = "GameServer.exe";
public:
	static void createNewGameProcess(std::string gameServerIP, network::PortsTriplet freePorts);
};

#endif // !GAME_PROCESS_CREATOR_H_