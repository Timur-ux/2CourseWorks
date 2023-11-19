#ifndef MOB_FABRIC_H_
#define MOB_FABRIC_H_

#include "Mob.hpp"
#include <concepts>
#include <type_traits>

template <typename T>
concept TConcretMob = std::is_base_of_v<Mob, T>;

class MobFabric {
public:
	template <TConcretMob TMob>
	static TMob & create();
};

#endif // MOB_FABRIC_H_