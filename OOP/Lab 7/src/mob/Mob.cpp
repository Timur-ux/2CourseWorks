#include "mob/Mob.hpp"

std::string Mob::getName() const {
    return name;
}

long long Mob::getId() const {
    return id;
}
std::ostream & operator<<(std::ostream & os, enumMobType type) {
    os << static_cast<int>(type);

    return os;
}

std::istream & operator>>(std::istream & is, enumMobType & type) {
    int intType;

    is >> intType;
    type = enumMobType{ intType };

    return is;
}

