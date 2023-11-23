#include "Serializer.hpp"

ISerializer & LocationSerializer::serialize(std::ostream & os) {
	auto mobs = location->getMobsData();

	for (auto it = std::cbegin(mobs)
		, last = std::cend(mobs); it != last; ++it) {
		auto & mobData = it->second;
		os << mobData.getId()
			<< " " << mobData.getMobType()
			<< " " << mobData.getMob()->getName()
			<< " " << mobData.getPosition()
			<< '\n';
	}

	return *this;
}

ISerializer & LocationSerializer::deserialize(std::istream & is) {
	std::string data;
	while (std::getline(is, data)) {
		std::stringstream dataStream(data);
		int id;
		enumMobType type;
		std::string name;
		Position pos;

		dataStream >> id >> type >> name >> pos;

		auto mob = MobFabric::create(type);

		MobData mobData(mob, pos, type);

		location->addMob(mobData);
	}

	return *this;
}

ISerializer & LocationSerializer::setLocation(std::shared_ptr<ILocation> _location) {
	location = _location;

	return *this;
}
