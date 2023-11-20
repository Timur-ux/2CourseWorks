#ifndef LOCATION_H_
#define LOCATION_H_

#include <map>
#include <string>
#include <memory>
#include <stdexcept>

#include "Mob.hpp"
#include "UndoManager.hpp"

struct Position {
	double x;
	double y;

	friend std::istream & operator>>(std::istream & is, Position & pos);
};

class ILocation;

struct MobData {

	std::shared_ptr<Mob> mob;
	Position position;
	MobType type;
	int id = -1;

	MobData() = default;
	MobData(std::shared_ptr<Mob> _mob, Position _position, MobType _type)
		: mob(mob), position(_position), type(_type) {}

	MobData(MobData & other) :
		mob(other.mob)
		, position(other.position)
		, id(other.id) {}
};

class LocationRedactor;
class ILocation {
public:
	virtual ILocation & addMob(MobData _mobData) = 0;
	virtual ILocation & moveMob(int id, Position newPos) = 0;
	virtual ILocation & removeMob(int id) = 0;
	virtual MobData & getMobDataBy(int id) = 0;
	virtual std::map<int, MobData> & getMobsData() = 0;
};

class DangeonLocation : ILocation {
private:
	double width = 500;
	double height = 500;
	std::map<int, MobData> mobs;
	int freeId = 0;
public:
	DangeonLocation() = default;

	ILocation & addMob(MobData _mobData) override;
	ILocation & moveMob(int id, Position newPos) override;
	ILocation & removeMob(int id) override;
	MobData & getMobDataBy(int id) override;
	std::map<int, MobData> & getMobsData() override;

	// TODO: add removeMob and connect UndoManager 
};

#endif // LOCATION_H_