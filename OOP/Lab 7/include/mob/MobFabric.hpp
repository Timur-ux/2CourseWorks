#ifndef MOB_FABRIC_H_
#define MOB_FABRIC_H_

#include "allConcretMobsHeaders.hpp"
#include "MobTypeCvt.hpp"
#include <memory>

class MobFabric {
public:
    template <TConcretMob TMob>
    static std::shared_ptr<TMob> create(std::string name = "");

    static std::shared_ptr<Mob> create(std::string strType, std::string name = "");

    static std::shared_ptr<Mob> create(enumMobType enumType, std::string name = "");
};

inline std::shared_ptr<Mob> MobFabric::create(std::string strType, std::string name) {
    return create(MobTypeCvt::to_enum(strType), name);
}

inline std::shared_ptr<Mob> MobFabric::create(enumMobType enumType, std::string name) {
    switch (enumType) {
    case enumMobType::KnightStranger:
        return create<KnightStranger>(name);
    case enumMobType::Elf:
        return create<Elf>(name);
    case enumMobType::Dragon:
        return create<Dragon>(name);
    case enumMobType::BaseMob:
        throw std::invalid_argument("Can not create mob with type: BaseMob");
    }

    throw std::invalid_argument("Undefined mob type: " + static_cast<int>(enumType));
}

template<TConcretMob TMob>
inline std::shared_ptr<TMob> MobFabric::create(std::string name) {
    return std::make_shared<TMob>(name);
}

#endif // MOB_FABRIC_H_
