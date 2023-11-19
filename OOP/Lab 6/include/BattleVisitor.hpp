#ifndef BATTLE_VISITOR_H_
#define BATTLE_VISITOR_H_
#include "Mob.hpp"

class IVisitor {
public:
	virtual bool visit(KnightStranger & knight) = 0;
	virtual bool visit(Elf & elf) = 0;
	virtual bool visit(Dragon & dragon) = 0;
};

class KnightStrangerVisitor : IVisitor {
public:
	virtual bool visit(KnightStranger & knight) override;
	virtual bool visit(Elf & elf) override;
	virtual bool visit(Dragon & dragon) override;
};

class ElfVisitor : IVisitor {
public:
	virtual bool visit(KnightStranger & knight) override;
	virtual bool visit(Elf & elf) override;
	virtual bool visit(Dragon & dragon) override;
};

class DragonVisitor : IVisitor {
public:
	virtual bool visit(KnightStranger & knight) override;
	virtual bool visit(Elf & elf) override;
	virtual bool visit(Dragon & dragon) override;
};

#endif // BATTLE_VISITOR_H_