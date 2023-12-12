#ifndef BATTLE_MANAGER_H_
#define BATTLE_MANAGER_H_

#include <memory>
#include <list>
#include <type_traits>
#include <thread>
#include <chrono>
#include <shared_mutex>

#include "BattleVisitor.hpp"
#include "../Location.hpp"

using namespace std::chrono_literals;

class SafeBool {
private:
    mutable std::shared_mutex mutex;
    bool value;
public:
    SafeBool(bool _value) : value(_value) {}
    SafeBool & operator=(bool _value);
    operator bool() const;
};

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
    SafeBool isNowBattle{ false };
public:
    BattleManager() = default;
    BattleManager(std::shared_ptr<ILocation> _location) : battleLocation(_location) {}

    virtual void provideBattleRound();
    void startContiniousBattle(std::chrono::milliseconds dtime);
    void stopBattle();
    virtual std::list<BattleEvent> & getDeadListForLastRound();
    virtual void setBattleLocation(std::shared_ptr<ILocation> location);
};

#endif // BATTLE_MANAGER_H_