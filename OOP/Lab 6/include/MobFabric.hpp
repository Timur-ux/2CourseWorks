#ifndef MOB_FABRIC_H_
#define MOB_FABRIC_H_

#include "Mob.hpp"
#include <memory>

class MobFabric {
public:
	template <TConcretMob TMob>
	static std::shared_ptr<TMob> create();
};

#endif // MOB_FABRIC_H_