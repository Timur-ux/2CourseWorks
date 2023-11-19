#include "LocationRedactor.hpp"

void LocationRedactor::inputCommand(Command command) {
	if (command == Command::addMob) {
		Mob mob;
		std::string type;
		Position position;
		inStream >> type >> position;
		if (type == "KnightStranger") {
			mob = MobFabric::create<KnightStranger>();
		}
		else if (type == "Elf") {
			mob = MobFabric::create<Elf>();
		}
		else if (type == "Dragon") {
			mob = MobFabric::create<Dragon>();
		}
		else {
			throw std::invalid_argument("LocationRedactor: Undefined mob type");
		}
		addMob(MobData(mob, position));
	}
}