#include "Serializer.hpp"

ISerializer & LocationSerializer::serialize(std::ostream & os) {
	auto mobs = location->getMobsData();

	for (auto it = std::cbegin(mobs)
		, last = std::cend(mobs); it != last; ++it) {
		os << it->second;
	}

	return *this;
}

ISerializer & LocationSerializer::deserialize(std::istream & is) {
	MobData mobData;
	while (is >> mobData) {
		location->addMob(mobData);
	}

	return *this;
}

ISerializer & LocationSerializer::setLocation(std::shared_ptr<ILocation> _location) {
	location = _location;

	return *this;
}