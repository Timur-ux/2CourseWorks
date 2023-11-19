#ifndef BATTLE_MANAGER_H_
#define BATTLE_MANAGER_H_
#include <memory>
#include "Location.hpp"

class BattleManager {
protected:
	std::shared_ptr<ILocation> battleLocation;
public:
	virtual void provideBattleRound();
	virtual void setBattleLocation(std::shared_ptr<ILocation> location);
};

#endif // BATTLE_MANAGER_H_