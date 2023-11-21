#include "Location.hpp"

std::istream & operator>>(std::istream & is, Position & pos) {
	is >> pos.x >> pos.y;

	return is;
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


LocationLogObserver & LocationLogObserver::onAdd(const MobData & mobData, const Position & newPos) {
	std::shared_ptr<LocationUpdateData> data = std::make_shared<LocationUpdateData>();
	std::stringstream dataStream;
	dataStream << "Id: " << mobData.getId() << ", action: add mob" << "\n";

	data->setData(dataStream.str());
	std::shared_ptr<IUpdateData> baseData = data;
	update(data);
}