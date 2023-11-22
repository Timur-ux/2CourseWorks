#ifndef BATTLE_MANAGER_H_
#define BATTLE_MANAGER_H_
#include <memory>
#include <list>
#include <type_traits>

#include "BattleVisitor.hpp"
#include "Location.hpp"

struct DeadEvent {
	MobData & attacker;
	MobData & defender;

	DeadEvent(std::remove_const_t<MobData &> _attacker, std::remove_const_t<MobData &> _defender) :
		attacker(_attacker)
		, defender(_defender) {}
};

class BattleManager {
protected:
	std::shared_ptr<ILocation> battleLocation;
	std::list<DeadEvent> deadlist;
public:
	virtual void provideBattleRound(double attackDistance);
	virtual std::list<DeadEvent> getDeadListForLastRound();
	virtual void setBattleLocation(std::shared_ptr<ILocation> location);
};

#endif // BATTLE_MANAGER_H_