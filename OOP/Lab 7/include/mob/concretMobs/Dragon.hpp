#ifndef DRAGON_H_
#define DRAGON_H_

#include "../Mob.hpp"

constexpr unsigned int DragonAttackRange{ 30 };
constexpr unsigned int DragonMoveRange{ 50 };

class Dragon : public Mob {
public:
    Dragon(std::string _name = "Unnamed dragon") : Mob(_name, DragonAttackRange, DragonMoveRange) {}
    bool accept(IBattleVisitor & visitor) override;
};

template <>
struct MobTypeAs<Dragon> {
    static constexpr int asInt = static_cast<int>(enumMobType::Dragon);
    static constexpr std::string asString = "Dragon";
};

#endif