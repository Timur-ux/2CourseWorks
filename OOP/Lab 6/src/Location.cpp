#include "Location.hpp"

std::istream & operator>>(std::istream & is, Position & pos) {
	is >> pos.x >> pos.y;

	return is;
}

std::ostream & operator<<(std::ostream & os, const Position & pos) {
	os << pos.getX() << " " << pos.getY();

	return os;
}

std::ostream & operator<<(std::ostream & os, const Position && pos) {
	os << (const Position &)pos;

	return os;
}

std::ostream & operator<<(std::ostream & os, const MobData & _mobData) {
	os << "Id: " << _mobData.getId() << std::endl
		<< "type: " << MobTypeCvt::to_string(_mobData.getMobType()) << std::endl
		<< "name: " << replace(_mobData.getMob()->getName(), ' ', '_') << std::endl
		<< "position: " << _mobData.getPosition() << std::endl;

	return os;
}

std::istream & operator>>(std::istream & is, MobData & _mobData) {
	std::string temp, type, name;
	int id;
	Position pos;

	if (not(is >> temp)) {
		return is;
	}

	is >> id >> temp >> type >> temp >> name >> temp >> pos;
	name = replace(name, '_', ' ');

	_mobData.id = id;
	_mobData.mob = MobFabric::create(type, name);
	_mobData.type = MobTypeCvt::to_enum(type);
	_mobData.position = pos;

	return is;
}

int MobData::getId() const {
	return id;
}

Position MobData::getPosition() const {
	return position;
}

enumMobType MobData::getMobType() const {
	return type;
}

std::shared_ptr<const Mob> MobData::getMob() const {
	return std::shared_ptr<const Mob>(mob);
}

MobData & DangeonLocation::getMobDataBy(int id) {
	auto mobIt = mobs.find(id);
	if (mobIt == std::end(mobs)) {
		throw std::invalid_argument("Undefined mob id: " + std::to_string(id));
	}

	return mobIt->second;
}

std::string LocationUpdateData::asString() {
	std::stringstream dataStream;
	dataStream << "Id: " << mobData->getId() << "; action: " << action << "; " << additionalArgs;

	return dataStream.str();
}

LocationLogObserver & LocationLogObserver::onAdd(const MobData & mobData) {
	auto data = std::make_shared<LocationUpdateData>(
		std::make_shared<const MobData>(mobData)
	);

	std::stringstream argsStream;
	argsStream << "position: " << mobData.getPosition();

	data->action = "add";
	data->additionalArgs = argsStream.str();
	update(data);

	return *this;
}
LocationLogObserver & LocationLogObserver::onMove(const MobData & mobData, const Position & oldPos, const Position & newPos) {
	auto data = std::make_shared<LocationUpdateData>(
		std::make_shared<const MobData>(mobData)
	);

	std::stringstream argsStream;
	argsStream << "from " << oldPos << " to " << newPos;

	data->action = "move";
	data->additionalArgs = argsStream.str();

	update(data);
	return *this;
}

LocationLogObserver & LocationLogObserver::onRemove(const MobData & mobData) {
	auto data = std::make_shared<LocationUpdateData>(
			std::make_shared<const MobData>(mobData)
	);
	data->action = "remove";
	update(data);

	return *this;
}

const std::map<int, MobData> & DangeonLocation::getMobsData() {
	return mobs;
}

DangeonLocation & DangeonLocation::setLogObserver(std::shared_ptr<LocationLogObserver> _logObserver) {
	logObserver = _logObserver;

	return *this;
}

DangeonLocation & DangeonLocation::setUndoManager(std::shared_ptr<DangeonUndoManager> _undoManager) {
	undoManager = _undoManager;

	return *this;
}