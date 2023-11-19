#ifndef BATTLE_VISITOR_H_
#define BATTLE_VISITOR_H_

#include <concepts>

#include "Mob.hpp"

namespace BVData {
	constexpr std::vector<std::vector<bool>> beatMap{
		{false, false, true},
		{true, false, false},
		{true, true, true}
	}
} // namespace battleVisitorData

class IVisitor {
public:
	virtual bool visit(KnightStranger & knight) = 0;
	virtual bool visit(Elf & elf) = 0;
	virtual bool visit(Dragon & dragon) = 0;
};

template <TConcretMob TMob>
class Visitor : IVisitor {
public:
	bool visit(KnightStranger & knight) override {
		return BVData::beatMap[MobTypeAs<TMob>::asInt][MobTypeAs<KnightStranger>::asInt];
	};
	bool visit(Elf & elf) override {
		return BVData::beatMap[MobTypeAs<TMob>::asInt][MobTypeAs<Elf>::asInt];
	};
	bool visit(Dragon & dragon) override {
		return BVData::beatMap[MobTypeAs<TMob>::asInt][MobTypeAs<Dragon>::asInt];
	};
};

bool KnightStranger::accept(IVisitor & visitor) {
	return visitor.visit(*this);
}

bool Elf::accept(IVisitor & visitor) {
	return visitor.visit(*this);
}

bool Dragon::accept(IVisitor & visitor) {
	return visitor.visit(*this);
}

#endif // BATTLE_VISITOR_H_