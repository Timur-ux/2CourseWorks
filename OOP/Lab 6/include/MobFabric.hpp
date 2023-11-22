#ifndef MOB_FABRIC_H_
#define MOB_FABRIC_H_

#include "Mob.hpp"
#include <memory>

class MobFabric {
public:
	template <TConcretMob TMob>
	static std::shared_ptr<TMob> create();

	static std::shared_ptr<Mob> create(std::string strType);

	static std::shared_ptr<Mob> create(enumMobType enumType);
};

inline std::shared_ptr<Mob> MobFabric::create(std::string strType) {
	return create(MobTypeCvt::to_enum(strType));
}

inline std::shared_ptr<Mob> MobFabric::create(enumMobType enumType) {
	switch (enumType) {
	case enumMobType::KnightStranger:
		return create<KnightStranger>();
	case enumMobType::Elf:
		return create<Elf>();
	case enumMobType::Dragon:
		return create<Dragon>();
	case enumMobType::BaseMob:
		throw std::invalid_argument("Can not create mob with type: BaseMob");
	}

	throw std::invalid_argument("Undefined mob type: " + static_cast<int>(enumType));
}


#endif // MOB_FABRIC_H_