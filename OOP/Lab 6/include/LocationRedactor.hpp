#ifndef LOCATION_REDACTOR_H_
#define LOCATION_REDACTOR_H_

#include <string>
#include <memory>
#include <iostream>
#include <fstream>

#include "Location.hpp"
#include "MobFabric.hpp"
#include "Observer.hpp"
#include "BattleManager.hpp"
#include "UndoManager.hpp"

enum class Command {
	addMob,
	removeMob,
	printMobs,
	moveMob,
	startBattleRound,
	undo,
	serializeMobs,
	deserializeMobs
};

class LocationRedactor {
private:
	std::istream & inStream = std::cin;
	std::ostream & outStream = std::cout;

	std::shared_ptr<LogObserver> observer;
	std::shared_ptr<ILocation> location;
	std::shared_ptr<BattleManager> battleManager;

	LocationRedactor & addMob();
	LocationRedactor & removeMob();
	LocationRedactor & printMobs();
	LocationRedactor & moveMob();
	LocationRedactor & startBattleRound();
	LocationRedactor & undo();
	LocationRedactor & serializeMobs();
	LocationRedactor & deserializeMobs();
public:
	LocationRedactor() = default;

	LocationRedactor & inputCommand(Command command);

	LocationRedactor & setObserver(std::shared_ptr<LogObserver> _observer);
	LocationRedactor & setLocation(std::shared_ptr<ILocation> _location);
	LocationRedactor & setBattleManager(std::shared_ptr<BattleManager> _battleManager);
};

#endif // IO_MANAGER_H_