#ifndef BATTLE_VISITOR_H_
#define BATTLE_VISITOR_H_

#include <concepts>
#include <vector>

#include "Mob.hpp"

namespace BVData {
	static std::vector<std::vector<bool>> beatMap{
		{false, false, true},
		{true, false, false},
		{true, true, true}
	};
}; // namespace battleVisitorData

class IBattleVisitor {
public:
	virtual bool visit(KnightStranger & knight) = 0;
	virtual bool visit(Elf & elf) = 0;
	virtual bool visit(Dragon & dragon) = 0;
};

template <TConcretMob TMob>
class Visitor : public IBattleVisitor {
public:
	bool visit(KnightStranger & knight) override {
		return BVData::beatMap.at(MobTypeAs<TMob>::asInt)[MobTypeAs<KnightStranger>::asInt];
	};
	bool visit(Elf & elf) override {
		return BVData::beatMap.at(MobTypeAs<TMob>::asInt)[MobTypeAs<Elf>::asInt];
	};
	bool visit(Dragon & dragon) override {
		return BVData::beatMap.at(MobTypeAs<TMob>::asInt)[MobTypeAs<Dragon>::asInt];
	};
};

bool KnightStranger::accept(IBattleVisitor & visitor) {
	return visitor.visit(*this);
}

bool Elf::accept(IBattleVisitor & visitor) {
	return visitor.visit(*this);
}

bool Dragon::accept(IBattleVisitor & visitor) {
	return visitor.visit(*this);
}

#endif // BATTLE_VISITOR_H_