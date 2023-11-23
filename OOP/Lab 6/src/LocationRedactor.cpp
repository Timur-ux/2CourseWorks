#include "LocationRedactor.hpp"

void printMobData(std::ostream & out, const MobData & data);

LocationRedactor & LocationRedactor::inputCommand(Command command) {
	switch (command) {
	case Command::addMob:
		addMob();
		break;
	case Command::removeMob:
		removeMob();
		break;
	case Command::printMobs:
		printMobs();
		break;
	case Command::moveMob:
		moveMob();
		break;
	case Command::startBattleRound:
		startBattleRound();
		break;
	case Command::undo:
		undo();
		break;
	case Command::serializeMobs:
		serializeMobs();
		break;
	case Command::deserializeMobs:
		deserializeMobs();
		break;
	}

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

LocationRedactor & LocationRedactor::setOStream(std::shared_ptr<std::ostream> _outStream) {
	outStream = _outStream;

	return *this;
}

LocationRedactor & LocationRedactor::setIStream(std::shared_ptr<std::istream> _inStream) {
	inStream = _inStream;

	return *this;
}


LocationRedactor & LocationRedactor::addMob() {
	std::shared_ptr<Mob> mob;
	enumMobType mobType;

	std::string inputtedType;
	Position position;

	*outStream << "Input <type> <position X> <position Y>: ";
	*inStream >> inputtedType >> position;

	if (inputtedType == "KnightStranger") {
		mob = MobFabric::create<KnightStranger>();
		mobType = enumMobType::KnightStranger;
	}
	else if (inputtedType == "Elf") {
		mob = MobFabric::create<Elf>();
		mobType = enumMobType::Elf;
	}
	else if (inputtedType == "Dragon") {
		mob = MobFabric::create<Dragon>();
		mobType = enumMobType::Dragon;
	}
	else {
		throw std::invalid_argument(std::string("LocationRedactor: Undefined mob type -- ") + inputtedType);
	}

	location->addMob(MobData(mob, position, mobType));
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
		const MobData & data = it->second;
		printMobData(*outStream, data);
		*outStream << std::endl;
	}

	return *this;
}

LocationRedactor & LocationRedactor::moveMob() {
	int id;
	Position newPos;

	*outStream << "Input <Mob's Id> <new Position>: ";
	*inStream >> id >> newPos;
	location->moveMob(id, newPos);

	return *this;
}

LocationRedactor & LocationRedactor::startBattleRound() {
	double attackDistance;

	*outStream << "Input <attack distance>";
	*inStream >> attackDistance;

	battleManager->provideBattleRound(attackDistance);
	std::list<DeadEvent> deadlist = battleManager->getDeadListForLastRound();

	for (auto & deadEvent : deadlist) {
		*outStream << "Attacker: ";
		printMobData(*outStream, deadEvent.attacker);
		*outStream << "Defender: ";
		printMobData(*outStream, deadEvent.defender);
		*outStream << std::endl;
	}

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
	*inStream >> outName;

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
	*inStream >> inputName;

	if (inputName.size() == 0) {
		inputName = defaultInputName;
	}

	std::ifstream file(inputName);
	serializer->deserialize(file);

	return *this;
}

void printMobData(std::ostream & out, const MobData & data) {
	out << "Id: " << data.getId() << std::endl
		<< "type: " << MobTypeCvt::to_string(data.getMobType()) << std::endl
		<< "name: " << data.getMob()->getName() << std::endl;
}
