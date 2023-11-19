#ifndef MOB_H_
#define MOB_H_

namespace MobParameters {
	enum class Status {
		alive = 0,
		died = 1
	};
}

class IVisitor;

class Mob {
protected:
	MobParameters::Status status;
	std::string name;
public:
	virtual void attack(Mob & other);
	virtual std::string getName();
	virtual double getHealth();
	virtual double getAttackRange();
	virtual void visit(IVisitor & visitor);
};

class KnightStranger : public Mob {};
class Elf : public Mob {};
class Dragon : public Mob {};

#endif // MOB_H_