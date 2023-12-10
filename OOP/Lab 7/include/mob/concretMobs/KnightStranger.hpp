#ifndef KNIGHT_STRANGER_H_
#define KNIGHT_STRANGER_H_

#include "../Mob.hpp"

constexpr unsigned int KnightStrangerAttackRange{ 10 };
constexpr unsigned int KnightStrangerMoveRange{ 30 };

class KnightStranger : public Mob {
public:
    KnightStranger(std::string _name = "Unnamed knight") : Mob(_name, KnightStrangerAttackRange, KnightStrangerMoveRange) {}
    bool accept(IBattleVisitor & visitor) override;
};

template <>
struct MobTypeAs<KnightStranger> {
    static constexpr int asInt = static_cast<int>(enumMobType::KnightStranger);
    static constexpr std::string asString = "KnightStranger";
};

#endif