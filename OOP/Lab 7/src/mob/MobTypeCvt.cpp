#include "mob/MobTypeCvt.hpp"

std::string MobTypeCvt::to_string(enumMobType type) {
    return enum2String[type];
}

enumMobType MobTypeCvt::to_enum(std::string type) {
    if (string2Enum.find(type) == string2Enum.end()) {
        throw std::invalid_argument("Undefined type given to MobTypeCvt: " + type);
    }

    return string2Enum[type];
}