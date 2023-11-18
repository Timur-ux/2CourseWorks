#ifndef IO_MANAGER_H_
#define IO_MANAGER_H_

#include <string>
#include <memory>
#include <iostream>
#include "Location.hpp"
#include "Mob.hpp"
#include "Observer.hpp"

enum class Command {
	addMob,
	removeMob,
	printMobs,
	moveMob,
	startBattleRound,
	startBattleTillEnd,
	undo
};

class DangeonRedactor {
private:
	std::shared_ptr<IObserver> observer;
	std::shared_ptr<ILocation> dangeonLocation;
	std::shared_ptr<std::ostream> output;

	DangeonRedactor & addMob();
	DangeonRedactor & removeMob();
	DangeonRedactor & printMobs();
	DangeonRedactor & moveMob();
	DangeonRedactor & startBattleRound();
	DangeonRedactor & startBattleTillEnd();
	DangeonRedactor & undo();
public:
	DangeonRedactor() = default;

	enum class Command;

	void inputCommand(Command command) {
		switch (command) {
			// case 1:
			// 	command1();
			// 	break;
			// case 2:
			// 	command1();
			// 	break;
			//...
		}
	}

	DangeonRedactor & setObserver(std::shared_ptr<IObserver> _observer);
	DangeonRedactor & setLocation(std::shared_ptr<ILocation> _location);
	DangeonRedactor & setOutput(std::shared_ptr<std::ostream> _os);
};

#endif // IO_MANAGER_H_