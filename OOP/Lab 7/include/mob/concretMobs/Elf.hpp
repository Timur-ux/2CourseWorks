#ifndef ELF_H_
#define ELF_H_

#include "../Mob.hpp"

constexpr unsigned int ElfAttackRange{ 50 };
constexpr unsigned int ElfMoveRange{ 10 };

class Elf : public Mob {
public:
    Elf(std::string _name = "Unnamed elf") : Mob(_name, ElfAttackRange, ElfMoveRange) {}
    bool accept(IBattleVisitor & visitor) override;
};

template <>
struct MobTypeAs<Elf> {
    static constexpr int asInt = static_cast<int>(enumMobType::Elf);
    static constexpr std::string asString = "Elf";
};

#endif