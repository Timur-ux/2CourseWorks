#ifndef LOCATION_H_
#define LOCATION_H_
#include <map>
#include "Mob.hpp"

using Position = struct {
	double x;
	double y;
};

struct MobData {
	IMob mob;

	int id;
	std::string name;
	Position position;
};

class ILocation {
protected:
	std::map<int, MobData> mobs;
public:
	virtual void addMob(IMob & _mob) = 0;
	virtual void addMob(IMob && _mob) noexcept = 0;
	virtual void moveMob(int id, Position newPos) {
		mobs[id].position = newPos;
	};
	virtual void removeMob(int id) = 0;
};

class DangeonLocation : ILocation {

};

#endif // LOCATION_H_