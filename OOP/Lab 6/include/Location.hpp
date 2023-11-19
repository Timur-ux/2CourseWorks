#ifndef LOCATION_H_
#define LOCATION_H_

#include <map>
#include <string>
#include <memory>
#include <stdexcept>

#include "Mob.hpp"
#include "UndoManager.hpp"

using Position = struct {
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
	MobData(Mob _mob, Position _position, MobType _type)
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
	virtual ILocation & serialize(std::ostream & out) = 0;
	virtual ILocation & deserialize(std::istream & in) = 0;
	virtual ILocation & undo() = 0;
	virtual std::map<int, MobData> & getMobsData() = 0;
};

class DangeonLocation : ILocation {
private:
	double width = 500;
	double height = 500;
	std::map<int, MobData> mobs;
	int freeId = 0;
	std::shared_ptr<DangeonUndoManager> undoManager;
public:
	DangeonLocation() = default;

	ILocation & addMob(MobData _mobData) override;
	ILocation & moveMob(int id, Position newPos) override;
	ILocation & removeMob(int id) override;
	ILocation & serialize(std::ostream & out) override;
	ILocation & deserialize(std::istream & in) override;
	ILocation & undo() override;
	std::map<int, MobData> & getMobsData() override;

	// TODO: add removeMob and connect UndoManager 
};

#endif // LOCATION_H_