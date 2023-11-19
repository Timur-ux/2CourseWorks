#ifndef LOCATION_REDACTOR_H_
#define LOCATION_REDACTOR_H_

#include <string>
#include <memory>
#include <iostream>

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
	startBattleTillEnd,
	undo,
	serializeMobs,
	deserializeMobs
};

class LocationRedactor {
private:
	std::istream & inStream = std::cin;

	std::shared_ptr<LogObserver> observer;
	std::shared_ptr<ILocation> location;
	std::shared_ptr<BattleManager> battleManager;
	std::shared_ptr <IUndoManager> undoManager;

	LocationRedactor & addMob(MobData ? &data);
	LocationRedactor & removeMob(int id);
	LocationRedactor & printMobs();
	LocationRedactor & moveMob(int id, Position from, Position to);
	LocationRedactor & startBattleRound();
	LocationRedactor & startBattleTillEnd();
	LocationRedactor & undo();
	LocationRedactor & serializeMobs(std::string outFileName = "mobsDump.txt");
	LocationRedactor & deserializeMobs(std::string inFileName = "mobDump.txt");
public:
	LocationRedactor() = default;

	void inputCommand(Command command);

	LocationRedactor & setObserver(std::shared_ptr<LogObserver> _observer);
	LocationRedactor & setLocation(std::shared_ptr<ILocation> _location);
	LocationRedactor & setBattleManager(std::shared_ptr<BattleManager> _battleManager);
};

#endif // IO_MANAGER_H_