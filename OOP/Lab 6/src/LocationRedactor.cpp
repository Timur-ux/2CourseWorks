#include "LocationRedactor.hpp"

void printMobData(std::ostream & out, MobData & data);

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

LocationRedactor & LocationRedactor::setObserver(std::shared_ptr<LogObserver> _observer) {
	observer = _observer;

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


LocationRedactor & LocationRedactor::addMob() {
	MobData mobData;
	std::string type;
	Position position;

	outStream << "Input <type> <position X> <position Y>: ";
	inStream >> type >> position;

	if (type == "KnightStranger") {
		mobData.mob = MobFabric::create<KnightStranger>();
		mobData.type = MobType::KnightStranger;
	}
	else if (type == "Elf") {
		mobData.mob = MobFabric::create<Elf>();
		mobData.type = MobType::Elf;
	}
	else if (type == "Dragon") {
		mobData.mob = MobFabric::create<Dragon>();
		mobData.type = MobType::Dragon;
	}
	else {
		throw std::invalid_argument(std::string("LocationRedactor: Undefined mob type -- ") + type);
	}

	location->addMob(mobData);
	return *this;
}

LocationRedactor & LocationRedactor::removeMob() {
	int id;

	outStream << "Input <Mob's id>: ";
	inStream >> id;
	location->removeMob(id);

	return *this;
}

LocationRedactor & LocationRedactor::printMobs() {
	outStream << "List of mobs on this location below:" << std::endl << std::endl;

	auto & data = location->getMobsData();
	for (auto it = std::begin(data)
			, last = std::end(data)
		; it != last; ++it) {
		MobData & data = it->second;
		printMobData(outStream, data);
		outStream << std::endl;
	}

	return *this;
}

LocationRedactor & LocationRedactor::moveMob() {
	int id;
	Position newPos;

	outStream << "Input <Mob's Id> <new Position>: ";
	inStream >> id >> newPos;
	location->moveMob(id, newPos);

	return *this;
}

LocationRedactor & LocationRedactor::startBattleRound() {
	double attackDistance;

	outStream << "Input <attack distance>";
	inStream >> attackDistance;

	battleManager->provideBattleRound(attackDistance);
	std::list<DeadEvent> deadlist = battleManager->getDeadListForLastRound();

	for (auto & deadEvent : deadlist) {
		outStream << "Attacker: ";
		printMobData(outStream, deadEvent.attacker);
		outStream << "Defender: ";
		printMobData(outStream, deadEvent.defender);
		outStream << std::endl;
	}

	return *this;
}

LocationRedactor & LocationRedactor::undo() {
	outStream << "Doing undo..." << std::endl;
	location->undo();

	return *this;
}

LocationRedactor & LocationRedactor::serializeMobs() {
	static std::string defaultOutName = "mobDump.txt";
	std::string outName;

	outStream << "Input <outputFileName> ( \"" << defaultOutName << "\" by default): ";
	inStream >> outName;

	if (outName.size() == 0) {
		outName = defaultOutName;
	}

	std::ofstream file(outName);
	location->serialize(file);

	return *this;
}

LocationRedactor & LocationRedactor::deserializeMobs() {
	static std::string defaultInputName = "mobDump.txt";
	std::string inputName;

	outStream << "Input <outputFileName> ( \"" << defaultInputName << "\" by default): ";
	inStream >> inputName;

	if (inputName.size() == 0) {
		inputName = defaultInputName;
	}

	std::ifstream file(inputName);
	location->deserialize(file);

	return *this;
}

void printMobData(std::ostream & out, MobData & data) {
	out << "Id: " << data.id << std::endl
		<< "type: " << mobTypeAsString[data.type] << std::endl
		<< "name: " << data.mob->getName() << std::endl;
}
