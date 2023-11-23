#ifndef LOCATION_REDACTOR_H_
#define LOCATION_REDACTOR_H_

#include <string>
#include <memory>
#include <iostream>
#include <fstream>

#include "Location.hpp"
#include "mob/MobFabric.hpp"
#include "Observer.hpp"
#include "battle/BattleManager.hpp"
#include "undoManager/UndoManager.hpp"
#include "Serializer.hpp"

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
	std::shared_ptr<std::istream> inStream = std::shared_ptr<std::istream>{ &std::cin };
	std::shared_ptr<std::ostream> outStream = std::shared_ptr<std::ostream>{ &std::cout };

	std::shared_ptr<ILocation> location;
	std::shared_ptr<BattleManager> battleManager;
	std::shared_ptr<LogObserver> logObserver;
	std::shared_ptr<LocationSerializer> serializer;
	std::shared_ptr<DangeonUndoManager> undoManager;

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
	LocationRedactor & setSerializer(std::shared_ptr<LocationSerializer> _serializer);
	LocationRedactor & setUndoManager(std::shared_ptr<DangeonUndoManager> _undoManager);
	LocationRedactor & setOStream(std::shared_ptr<std::ostream> _outStream);
	LocationRedactor & setIStream(std::shared_ptr<std::istream> _inStream);
};

#endif // IO_MANAGER_H_