#ifndef LOCATION_H_
#define LOCATION_H_

#include <map>
#include <string>
#include <stdexcept>

#include "Mob.hpp"

using Position = struct {
	double x;
	double y;
};

class ILocation;

struct MobData {

	IMob & mob;
	std::string name;
	Position position;
	int id;

	MobData(MobData & other) :
		mob(other.mob)
		, name(other.name)
		, position(other.position)
		, id(other.id) {}
};

class ILocation {
public:
	virtual ILocation & addMob(MobData _mobData) = 0;
	virtual ILocation & moveMob(int id, Position newPos) = 0;
	virtual ILocation & removeMob(int id) = 0;
};

class DangeonLocation : ILocation {
private:
	std::map<int, MobData> mobs;
	int freeId = 0;
public:
	DangeonLocation() = default;

	ILocation & addMob(MobData _mobData) override {
		_mobData.id = freeId++;
		mobs.emplace(std::make_pair(_mobData.id, _mobData));
	}

	ILocation & moveMob(int id, Position newPos) override {
		if (mobs.find(id) == mobs.end()) {
			throw std::invalid_argument("ILocation::moveMob error: Undefined mob's id");
		}
		mobs[id].position = newPos;

		return *this;
	};

	// TODO: add removeMob and connect UndoManager 
};

#endif // LOCATION_H_