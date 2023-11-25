#ifndef LOCATION_H_
#define LOCATION_H_

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <type_traits>

#include "mob/Mob.hpp"
#include "Observer.hpp"

struct Position {
	double x;
	double y;

	friend std::istream & operator>>(std::istream & is, Position & pos);
	friend std::ostream & operator<<(std::ostream & os, const Position & pos);
	friend std::ostream & operator<<(std::ostream & os, const Position && pos);

	double getX() const {
		return x;
	}

	double getY() const {
		return y;
	}
};

class DangeonLocation;
class BattleManager;
class MobData {
private:
	int id;
	std::shared_ptr<Mob> mob;
	Position position;
	enumMobType type;
public:
	friend DangeonLocation;
	friend BattleManager;

	MobData() = default;
	MobData(std::shared_ptr<Mob> _mob, Position _position, enumMobType _type, int _id = -1)
		: mob(_mob), position(_position), type(_type), id(_id) {}

	MobData(const MobData & other) :
		mob(other.mob)
		, position(other.position)
		, type(other.type)
		, id(other.id) {}



	int getId() const;
	Position getPosition() const;
	enumMobType getMobType() const;
	std::shared_ptr<const Mob> getMob() const;

	friend std::ostream & operator<<(std::ostream & os, const MobData & _mobData);
};

class ILocation {
public:
	virtual ILocation & addMob(MobData _mobData) = 0;
	virtual ILocation & moveMob(int id, Position newPos) = 0;
	virtual ILocation & removeMob(int id) = 0;
	virtual MobData & getMobDataBy(int id) = 0;
	virtual const std::map<int, MobData> & getMobsData() = 0;
};

class DangeonLocation : public ILocation {
private:
	double width = 500;
	double height = 500;
	std::map<int, MobData> mobs;
	std::shared_ptr<LocationLogObserver> logObserver;
	int freeId = 1;
public:
	DangeonLocation() = default;
	DangeonLocation(std::shared_ptr<LocationLogObserver> _logObserver) : logObserver(_logObserver) {}

	ILocation & addMob(MobData _mobData) override;
	ILocation & moveMob(int id, Position newPos) override;
	ILocation & removeMob(int id) override;
	MobData & getMobDataBy(int id) override;
	const std::map<int, MobData> & getMobsData() override;

	DangeonLocation & setLogObserver(std::shared_ptr<LogObserver> _logObserver);
};

#endif // LOCATION_H_