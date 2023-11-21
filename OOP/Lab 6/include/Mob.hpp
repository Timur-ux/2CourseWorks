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

enum class MobType {
	KnightStranger = 0,
	Elf = 1,
	Dragon = 2,
	BaseMob = 3
};

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
	Mob(std::string _name) : name(_name), status(MobParameters::Status::alive) {}
	virtual std::string getName() const;
	virtual bool accept(IVisitor & visitor) = 0;
};


class KnightStranger : public Mob {
public:
	bool accept(IVisitor & visitor) override;
};

class Elf : public Mob {
public:
	bool accept(IVisitor & visitor) override;
};

class Dragon : public Mob {
public:
	bool accept(IVisitor & visitor) override;
};

template<TConcretMob TMob>
struct MobTypeAs {
	MobType asInt;
	std::string asString;
};


template <>
struct MobTypeAs<Mob> {
	static constexpr MobType asInt = MobType::BaseMob;
	static constexpr std::string asString = "BaseMob";
};


template <>
struct MobTypeAs<KnightStranger> {
	static constexpr MobType asInt = MobType::KnightStranger;
	static constexpr std::string asString{ "KnightStranger" };
};

template <>
struct MobTypeAs<Elf> {
	static constexpr MobType asInt = MobType::Elf;
	static constexpr std::string asString{ "Elf" };
};

template <>
struct MobTypeAs<Dragon> {
	static constexpr MobType asInt = MobType::Dragon;
	static constexpr std::string asString{ "Dragon" };
};

inline std::map<MobType, const std::string> mobTypeAsString{
	{MobType::BaseMob, "BaseMob"},
	{MobType::KnightStranger, "KnightStranger"},
	{MobType::Elf, "Elf"},
	{MobType::Dragon, "Dragon"}
};
#endif // MOB_H_