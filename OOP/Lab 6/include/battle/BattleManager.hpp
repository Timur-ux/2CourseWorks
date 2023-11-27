#ifndef BATTLE_MANAGER_H_
#define BATTLE_MANAGER_H_
#include <memory>
#include <list>
#include <type_traits>

#include "BattleVisitor.hpp"
#include "Location.hpp"

struct BattleEvent {
    const MobData & attacker;
    const MobData & defender;

    BattleEvent(const MobData & _attacker, const MobData & _defender) :
        attacker(_attacker)
        , defender(_defender) {}
};

class BattleManager {
protected:
    std::shared_ptr<ILocation> battleLocation;
    std::list<BattleEvent> deadlist;
public:
    BattleManager() = default;
    BattleManager(std::shared_ptr<ILocation> _location) : battleLocation(_location) {}

    virtual void provideBattleRound(double attackDistance);
    virtual std::list<BattleEvent> & getDeadListForLastRound();
    virtual void setBattleLocation(std::shared_ptr<ILocation> location);
};

#endif // BATTLE_MANAGER_H_