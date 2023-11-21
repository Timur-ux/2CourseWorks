#include "UndoManager.hpp"

std::string StateAdd::toString() {
	std::stringstream stateStream;

	stateStream << "add "
		<< mobToAdd->getId()
		<< " " << mobTypeAsString[mobToAdd->getMobType()]
		<< " " << mobToAdd->getMob()->getName();

	return stateStream.str();
}

IState & StateAdd::fromString(std::string _data) {
	std::stringstream stateStream(_data);
	std::string action, strMobType, name;
	int id;

	stateStream >> action >> id >> strMobType >> name;

	MobType type = mobTypeAsEnum[strMobType];
	switch (type) { // TODO: поправить 
	case:
	}

}
