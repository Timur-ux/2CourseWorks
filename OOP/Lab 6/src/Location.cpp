#include "Location.hpp"
#include "Observer.hpp"

std::istream & operator>>(std::istream & is, Position & pos) {
	is >> pos.x >> pos.y;

	return is;
}

std::ostream & operator<<(std::ostream & os, const Position & pos) {
	os << "{" << pos.getX() << " " << pos.getY() << "}";

	return os;
}

std::ostream & operator<<(std::ostream & os, const Position && pos) {
	os << (const Position &)pos;

	return os;
}

std::ostream & operator<<(std::ostream & os, const MobData & _mobData) {
	os << "Id: " << _mobData.getId() << std::endl
		<< "type: " << MobTypeCvt::to_string(_mobData.getMobType()) << std::endl
		<< "name: " << _mobData.getMob()->getName() << std::endl
		<< "position: " << _mobData.getPosition() << std::endl;

	return os;
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

ILocation & DangeonLocation::addMob(MobData _mobData) {
	_mobData.id = freeId;
	mobs[freeId] = _mobData;
	++freeId;

	logObserver->onAdd(_mobData);

	return *this;
}

ILocation & DangeonLocation::moveMob(int id, Position newPos) {
	if (mobs.find(id) == std::end(mobs)) {
		throw std::invalid_argument("Location hasn't mob with id: " + std::to_string(id));
	}

	MobData & data = mobs[id];

	Position oldPos = data.getPosition();
	data.position = newPos;

	logObserver->onMove(data, oldPos, newPos);

	return *this;
}

ILocation & DangeonLocation::removeMob(int id) {
	auto mobIterator = mobs.find(id);
	if (mobIterator == std::end(mobs)) {
		throw std::invalid_argument("Location hasn't mob with id: " + std::to_string(id));
	}

	logObserver->onRemove(mobIterator->second);
	mobs.erase(mobIterator);

	return *this;
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
