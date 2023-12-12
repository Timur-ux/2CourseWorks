#include "LocationRedactor.hpp"

void LocationRedactor::doCommand(CommandType command) {
    switch (command) {
    case CommandType::addMob:
        addMob();
        break;
    case CommandType::removeMob:
        removeMob();
        break;
    case CommandType::printMobs:
        printMobs();
        break;
    case CommandType::startBattleRound:
        startBattleRound();
        break;
    case CommandType::startContiniousBattle:
        startContiniousBattle();
        break;
    case CommandType::undo:
        undo();
        break;
    case CommandType::serializeMobs:
        serializeMobs();
        break;
    case CommandType::deserializeMobs:
        deserializeMobs();
        break;
    case CommandType::printCommandList:
        printCommandList();
        break;
    }
}

LocationRedactor & LocationRedactor::inputCommand(std::string command) {
    auto commandIt = str2EnumCommand.find(command);
    if (commandIt == std::end(str2EnumCommand)) {
        throw std::invalid_argument("Undefined command: " + command);
    }

    doCommand(commandIt->second);

    return *this;
}

LocationRedactor & LocationRedactor::setObserver(std::shared_ptr<LogObserver> _logObserver) {
    logObserver = _logObserver;

    return *this;
}

LocationRedactor & LocationRedactor::setLocation(std::shared_ptr<ILocation> _location) {
    location = _location;

    return *this;
}

LocationRedactor & LocationRedactor::setBattleManager(std::shared_ptr<BattleManager> _battleManager) {
    battleManager = _battleManager;

    return *this;
}

LocationRedactor & LocationRedactor::setSerializer(std::shared_ptr<LocationSerializer> _serializer) {
    serializer = _serializer;

    return *this;
}

LocationRedactor & LocationRedactor::setUndoManager(std::shared_ptr<DangeonUndoManager> _undoManager) {
    undoManager = _undoManager;

    return *this;
}

LocationRedactor & LocationRedactor::setOStream(std::ostream * _outStream) {
    outStream = _outStream;

    return *this;
}

LocationRedactor & LocationRedactor::setIStream(std::istream * _inStream) {
    inStream = _inStream;

    return *this;
}

void LocationRedactor::printCommandList() {
    int i = 1;
    for (auto & command : str2EnumCommand) {
        *outStream << i++ << ") " << command.first << std::endl;
    }
}


LocationRedactor & LocationRedactor::addMob() {
    std::shared_ptr<Mob> mob;
    enumMobType mobType;

    std::string inputtedType, name;
    Position position;

    *outStream << "Input <type> <name with _> <position X> <position Y>: ";
    *inStream >> inputtedType >> name >> position;

    name = replace(name, '_', ' ');

    if (inputtedType == "KnightStranger") {
        mob = MobFabric::create<KnightStranger>(name);
        mobType = enumMobType::KnightStranger;
    }
    else if (inputtedType == "Elf") {
        mob = MobFabric::create<Elf>(name);
        mobType = enumMobType::Elf;
    }
    else if (inputtedType == "Dragon") {
        mob = MobFabric::create<Dragon>(name);
        mobType = enumMobType::Dragon;
    }
    else {
        throw std::invalid_argument(std::string("LocationRedactor: Undefined mob type -- ") + inputtedType);
    }

    MobData mobData(mob, position, mobType);
    location->addMob(mobData);

    return *this;
}

LocationRedactor & LocationRedactor::removeMob() {
    int id;

    *outStream << "Input <Mob's id>: ";
    *inStream >> id;

    location->removeMob(id);

    return *this;
}

LocationRedactor & LocationRedactor::printMobs() {
    *outStream << "List of mobs on this location below:" << std::endl << std::endl;

    auto & data = location->getMobsData();
    for (auto it = std::begin(data)
            , last = std::end(data)
        ; it != last; ++it) {
        *outStream << it->second << std::endl;
    }

    return *this;
}

LocationRedactor & LocationRedactor::startBattleRound() {
    double attackDistance;

    *outStream << "Battle starting..." << std::endl;

    battleManager->provideBattleRound();
    auto & deadlist = battleManager->getDeadListForLastRound();

    for (auto & deadEvent : deadlist) {
        *outStream
            << "Attacker: " << deadEvent.attacker << std::endl
            << "Defender: " << deadEvent.defender << std::endl
            << "--------------------------------" << std::endl;
    }

    for (auto & event : deadlist) {
        try {
            location->removeMob(event.defender.getId());
        }
        catch (std::invalid_argument & e) {
            continue;
        }
    }

    return *this;
}

LocationRedactor & LocationRedactor::startContiniousBattle() {
    constexpr auto dtime = 250ms;
    MobsMover mobMover(location, dtime);

    std::thread t1(printLocationEvery, location, 1000ms, 30s);
    std::thread t2(BattleManager::startContiniousBattle, battleManager, dtime);
    std::thread t3(std::ref(mobMover));

    t1.detach();
    t2.detach();
    t3.detach();

    std::this_thread::sleep_for(30s);

    battleManager->stopBattle();
    mobMover.stopMoving();

    return *this;
}

LocationRedactor & LocationRedactor::undo() {
    *outStream << "Doing undo..." << std::endl;
    undoManager->undo();

    return *this;
}

LocationRedactor & LocationRedactor::serializeMobs() {
    static std::string defaultOutName = "mobDump.txt";
    std::string outName;

    *outStream << "Input <outputFileName> ( \"" << defaultOutName << "\" by default): ";
    getline(*inStream, outName);

    if (outName.size() == 0) {
        outName = defaultOutName;
    }

    std::ofstream file(outName);
    serializer->serialize(file);

    return *this;
}

LocationRedactor & LocationRedactor::deserializeMobs() {
    static std::string defaultInputName = "mobDump.txt";
    std::string inputName;

    *outStream << "Input <outputFileName> ( \"" << defaultInputName << "\" by default): ";
    getline(*inStream, inputName);

    if (inputName.size() == 0) {
        inputName = defaultInputName;
    }

    std::ifstream file(inputName);
    if (not(file.is_open())) {
        std::cerr << "Cannot open: " << inputName << std::endl;
        return *this;
    }
    serializer->deserialize(file);

    return *this;
}

void printLocationEvery(std::shared_ptr<ILocation> location, std::chrono::milliseconds dtime, std::chrono::seconds duration) {
    std::chrono::seconds current = 0s;
    while (current <= duration) {
        location->drawMap();

        current += 1s;

        std::this_thread::sleep_for(dtime);
    }
}

void MobsMover::stopMoving() {
    isNowMoving = false;
}

void MobsMover::operator()() {
    static std::vector<std::pair<double, double>> moveDirections{
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };

    isNowMoving = true;
    while (isNowMoving) {
        auto & mobDatas = location->getMobsData();
        for (auto & pair : mobDatas) {
            const MobData & mobData = pair.second;
            if (mobData.getStatus() == MobParameters::Status::died) {
                continue;
            }

            std::pair<double, double> curDir = moveDirections[rand() % moveDirections.size()];
            double dx = curDir.first;
            double dy = curDir.second;

            mobData.getMob()->moveWithShift(dx, dy, dtime);
        }

        std::this_thread::sleep_for(dtime);
    }
}
