#ifndef LOCATION_REDACTOR_H_
#define LOCATION_REDACTOR_H_

#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include <map>

#include "Location.hpp"
#include "mob/MobFabric.hpp"
#include "Observer.hpp"
#include "battle/BattleManager.hpp"
#include "undoManager/UndoManager.hpp"
#include "Serializer.hpp"

enum class CommandType {
    addMob,
    removeMob,
    printMobs,
    moveMob,
    startBattleRound,
    undo,
    serializeMobs,
    deserializeMobs,
    printCommandList
};

const std::map<std::string, CommandType> str2EnumCommand{
    {"add", CommandType::addMob},
    {"remove", CommandType::removeMob},
    {"print", CommandType::printMobs},
    {"move", CommandType::moveMob},
    {"start battle round", CommandType::startBattleRound},
    {"undo", CommandType::undo},
    {"serialize", CommandType::serializeMobs},
    {"deserialize", CommandType::deserializeMobs},
    {"print commands list", CommandType::printCommandList}
};

class LocationRedactor {
private:
    std::istream * inStream = &std::cin;
    std::ostream * outStream = &std::cout;

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

    void doCommand(CommandType command);
public:
    LocationRedactor() = default;

    LocationRedactor & inputCommand(std::string command);
    void printCommandList();

    LocationRedactor & setObserver(std::shared_ptr<LogObserver> _observer);
    LocationRedactor & setLocation(std::shared_ptr<ILocation> _location);
    LocationRedactor & setBattleManager(std::shared_ptr<BattleManager> _battleManager);
    LocationRedactor & setSerializer(std::shared_ptr<LocationSerializer> _serializer);
    LocationRedactor & setUndoManager(std::shared_ptr<DangeonUndoManager> _undoManager);
    LocationRedactor & setOStream(std::ostream * _outStream);
    LocationRedactor & setIStream(std::istream * _inStream);
};

#endif // IO_MANAGER_H_