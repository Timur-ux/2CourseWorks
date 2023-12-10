#ifndef MOB_TYPE_CVT_H_
#define MOB_TYPE_CVT_H_
#include <map>

#include "Mob.hpp"

class MobTypeCvt {
private:
    static std::map<enumMobType, std::string> enum2String;
    static std::map<std::string, enumMobType> string2Enum;
public:
    static std::string to_string(enumMobType type);

    static enumMobType to_enum(std::string type);
};

inline std::map<enumMobType, std::string> MobTypeCvt::enum2String{
    {enumMobType::BaseMob, "BaseMob"},
    {enumMobType::KnightStranger, "KnightStranger"},
    {enumMobType::Elf, "Elf"},
    {enumMobType::Dragon, "Dragon"}
};

inline std::map<std::string, enumMobType> MobTypeCvt::string2Enum{
    {"BaseMob", enumMobType::BaseMob},
    {"KnightStranger", enumMobType::KnightStranger},
    {"Elf", enumMobType::Elf},
    {"Dragon", enumMobType::Dragon}
};

#endif