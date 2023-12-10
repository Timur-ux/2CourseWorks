#ifndef MOB_H_
#define MOB_H_

#include <string>
#include <map>
#include <concepts>
#include <type_traits>
#include <iostream>

#include "../Observer.hpp"
#include "../generators/idGenerator.hpp"

static IdGenerator idGenerator;

class Mob;

template <typename T>
concept TConcretMob = std::is_base_of_v<Mob, T>;

enum class enumMobType {
    KnightStranger = 0,
    Elf = 1,
    Dragon = 2,
    BaseMob = 3
};

std::ostream & operator<<(std::ostream & os, enumMobType type);
std::istream & operator>>(std::istream & is, enumMobType & type);

namespace MobParameters {
    enum class Status {
        alive = 0,
        died = 1
    };
}

class IBattleVisitor;
class BattleManager;
class Mob : public ILocationSubscriber {
protected:
    long long id;

    MobParameters::Status status;
    std::string name;
    unsigned int attackRange;
    unsigned int moveRange;

    IMobObserver * mobObserver;

    void setStatus(MobParameters::Status newStatus);
public:
    friend BattleManager;

    Mob(std::string _name, unsigned int _attackRange, unsigned int _moveRange)
        : name(_name)
        , status(MobParameters::Status::alive)
        , attackRange(_attackRange)
        , moveRange(_moveRange) {
        id = idGenerator.getId();
    }

    virtual ~Mob() {
        idGenerator.freeId(id);
    }

    virtual void moveWithShift(double dx, double dy, double dtime);

    MobParameters::Status getStatus() const;
    std::string getName() const;
    long long getId() const;

    virtual bool accept(IBattleVisitor & visitor) = 0;

    void setMobObserver(IMobObserver * other) override;
    long long getId() override;
    void on_move(double eta) override;
};

template <TConcretMob TMob>
struct MobTypeAs {};

#endif // MOB_H_