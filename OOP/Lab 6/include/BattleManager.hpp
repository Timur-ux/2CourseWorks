#ifndef BATTLE_MANAGER_H_
#define BATTLE_MANAGER_H_
#include <memory>
#include "Location.hpp"

class IBattleManager {
protected:
	std::shared_ptr<ILocation> battleLocation;
public:
	virtual void provideBattleRound() = 0;
	virtual void setBattleLocation(std::shared_ptr<ILocation> location) {
		battleLocation = location;
	}
};

#endif