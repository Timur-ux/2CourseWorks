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

int MobData::getId() const {
	return id;
}

Position MobData::getPosition() const {
	return position;
}

MobType MobData::getMobType() const {
	return type;
}

std::shared_ptr<const Mob> MobData::getMob() const {
	return std::shared_ptr<const Mob>(mob);
}

ILocation & DangeonLocation::addMob(MobData _mobData) {
	_mobData.id = freeId;
	mobs[freeId] = _mobData;

	return *this;
}

ILocation & DangeonLocation::moveMob(int id, Position newPos) {
	if (mobs.find(id) == std::end(mobs)) {
		throw std::invalid_argument("Location hasn't mob with id: " + std::to_string(id));
	}

	MobData & data = mobs[id];

	data.position = newPos;

	return *this;
}

std::string LocationUpdateData::asString() {
	std::stringstream dataStream;
	dataStream << "Id: " << mobData->getId() << "; action: " << action << " " << additionalArgs;
}

LocationLogObserver & LocationLogObserver::onAdd(const MobData & mobData) {
	auto data = std::make_shared<LocationUpdateData>(
		std::shared_ptr<const MobData>{ &mobData }
	);
	data->action = "add";
	update(data);
}
LocationLogObserver & LocationLogObserver::onMove(const MobData & mobData, const Position & newPos) {
	auto data = std::make_shared<LocationUpdateData>(
		std::shared_ptr<const MobData>{ &mobData }
	);
	data->action = "move";

	std::stringstream argsStream;
	argsStream << "from " << mobData.getPosition() << " to " << newPos;
	update(data);
}

LocationLogObserver & LocationLogObserver::onRemove(const MobData & mobData) {
	auto data = std::make_shared<LocationUpdateData>(
			std::shared_ptr<const MobData>{ &mobData }
	);
	data->action = "remove";
	update(data);
}
