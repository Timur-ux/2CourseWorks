#include "GameProcessCreator.hpp"
#include "print.hpp"
#include <sstream>

GameProcessCreator::gameApplicationName = "BullsAndCows.exe";
GameProcessCreator::games{};

void GameProcessCreator::createNewGameProcess(std::string gameServerIP, network::PortsTriplet freePorts)
{
	std::ostringstream oss;
	oss << gameApplicationName << ' ' << gameServerIP
		<< ' ' << freePorts.port1
		<< ' ' << freePorts.port2
		<< ' ' << freePorts.port3;
	
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	if (!CreateProcessA(
		NULL
		, (LPSTR)oss.str().c_str()
		, NULL
		, NULL
		, FALSE
		, 0
		, NULL
		, NULL
		, &si
		, &pi
	)) {
		printErr() << "Error: Creating game process failed" << std::endl;
		return;
	}

	games.push_back(pi);
}

GameProcessCreator::~GameProcessCreator() {
	for (auto & game : games) {
		TerminateProcess(game.hProcess, 0);
	}
}

