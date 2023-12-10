#ifndef BATTLE_VISITOR_H_
#define BATTLE_VISITOR_H_

#include <concepts>
#include <set>
#include <map>
#include <typeindex>
#include <typeinfo>
#include "../mob/allMobsHeadersInOneHeader.hpp"

#define TID(T) (std::type_index(typeid(T)))

namespace BVData {
    static std::map<std::type_index, std::set<std::type_index>> beatMap{
        {TID(KnightStranger), {TID(Dragon)}},
        {TID(Elf), {TID(KnightStranger)}},
        {TID(Dragon), {TID(KnightStranger), TID(Elf), TID(Dragon)}},
    };
}; // namespace BVData

class IBattleVisitor {
public:
    virtual bool visit(KnightStranger & knight) = 0;
    virtual bool visit(Elf & elf) = 0;
    virtual bool visit(Dragon & dragon) = 0;
};

template <TConcretMob TMob>
class Visitor : public IBattleVisitor {
private:
    std::set<std::type_index> beatableMobs = BVData::beatMap[TID(TMob)];
public:
    bool visit(KnightStranger & knight) {
        const auto tid = TID(KnightStranger);
        auto foundMob = beatableMobs.find(tid);

        return foundMob != std::end(beatableMobs);
    };
    bool visit(Elf & elf) override {
        const auto tid = TID(Elf);
        auto foundMob = beatableMobs.find(tid);

        return foundMob != std::end(beatableMobs);
    };
    bool visit(Dragon & dragon) override {
        const auto & tid = TID(Dragon);
        auto foundMob = beatableMobs.find(tid);

        return foundMob != std::end(beatableMobs);
    };
};

inline bool KnightStranger::accept(IBattleVisitor & visitor) {
    return visitor.visit(*this);
}

inline bool Elf::accept(IBattleVisitor & visitor) {
    return visitor.visit(*this);
}

inline bool Dragon::accept(IBattleVisitor & visitor) {
    return visitor.visit(*this);
}

#endif // BATTLE_VISITOR_H_