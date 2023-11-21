#ifndef MOB_H_
#define MOB_H_

#include <string>
#include <map>
#include <concepts>
#include <type_traits>

#include "Observer.hpp"

class Mob;

template <typename T>
concept TConcretMob = std::is_base_of_v<Mob, T>;

enum class enumMobType {
	KnightStranger = 0,
	Elf = 1,
	Dragon = 2,
	BaseMob = 3
};

std::ostream & operator<<(std::ostream & os, enumMobType type);
std::istream & operator>>(std::istream & is, enumMobType & type);

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
	Mob() = default;
public:
	Mob(std::string _name) : name(_name), status(MobParameters::Status::alive) {}
	virtual std::string getName() const;
	virtual bool accept(IVisitor & visitor) = 0;
};

class KnightStranger : public Mob {
public:
	KnightStranger(std::string _name = "Unnamed knight") : Mob(_name) {}
	bool accept(IVisitor & visitor) override;
};

class Elf : public Mob {
public:
	Elf(std::string _name = "Unnamed elf") : Mob(_name) {}
	bool accept(IVisitor & visitor) override;
};

class Dragon : public Mob {
public:
	Dragon(std::string _name = "Unnamed dragon") : Mob(_name) {}
	bool accept(IVisitor & visitor) override;
};

template <TConcretMob TMob>
struct MobTypeAs {};

struct MobTypeAs<KnightStranger> {
	static constexpr enumMobType asInt = enumMobType::KnightStranger;
	static constexpr std::string asString = "KnightStranger";
};

struct MobTypeAs<Elf> {
	static constexpr enumMobType asInt = enumMobType::Elf;
	static constexpr std::string asString = "Elf";
};

struct MobTypeAs<Dragon> {
	static constexpr enumMobType asInt = enumMobType::Dragon;
	static constexpr std::string asString = "Dragon";
};


#endif // MOB_H_