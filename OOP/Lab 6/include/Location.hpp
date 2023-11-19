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

	Mob mob;
	Position position;
	int id = -1;

	MobData(Mob _mob, Position _position)
		: mob(mob), position(_position) {}

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
	virtual ILocation & undo();
};

class DangeonLocation : ILocation {
private:
	double width = 500;
	double height = 500;
	std::map<int, MobData> mobs;
	int freeId = 0;
	std::shared_ptr<DangeonUndoManager> undoManager;
public:
	friend LocationRedactor;
	DangeonLocation() = default;

	ILocation & addMob(MobData _mobData) override;
	ILocation & moveMob(int id, Position newPos) override;
	ILocation & removeMob(int id) override;
	ILocation & serialize(std::ostream & out) override;
	ILocation & deserialize(std::istream & in) override;

	// TODO: add removeMob and connect UndoManager 
};

#endif // LOCATION_H_