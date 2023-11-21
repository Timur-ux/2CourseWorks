#ifndef MOB_FABRIC_H_
#define MOB_FABRIC_H_

#include "Mob.hpp"
#include <memory>

class MobFabric {
public:
	template <TConcretMob TMob>
	static std::shared_ptr<TMob> create();
	template <TConcretMob TMob>
	static std::shared_ptr<TMob> create(std::string strType);
};

#endif // MOB_FABRIC_H_

template<TConcretMob TMob>
inline std::shared_ptr<TMob> MobFabric::create(std::string strType) {
	if (strType == "KnightStranger") {
		return create<KnightStranger>();
	}

	if (strType == "Elf") {
		return create<Elf>();
	}

	if (strType == "Dragon") {
		return create<Dragon>();
	}

	throw std::invalid_argument("Undefined string representation of mob's type. Given: " + strType);
}
