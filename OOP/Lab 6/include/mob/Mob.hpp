#ifndef MOB_H_
#define MOB_H_

#include <string>
#include <map>
#include <concepts>
#include <type_traits>

#include "../Observer.hpp"

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

class IBattleVisitor;

class Mob {
protected:
	MobParameters::Status status;
	std::string name;
	Mob() = default;
public:
	Mob(std::string _name) : name(_name), status(MobParameters::Status::alive) {}

	virtual std::string getName() const;
	virtual bool accept(IBattleVisitor & visitor) = 0;
};

class KnightStranger : public Mob {
public:
	KnightStranger(std::string _name = "Unnamed knight") : Mob(_name) {}
	bool accept(IBattleVisitor & visitor) override;
};

class Elf : public Mob {
public:
	Elf(std::string _name = "Unnamed elf") : Mob(_name) {}
	bool accept(IBattleVisitor & visitor) override;
};

class Dragon : public Mob {
public:
	Dragon(std::string _name = "Unnamed dragon") : Mob(_name) {}
	bool accept(IBattleVisitor & visitor) override;
};

template <TConcretMob TMob>
struct MobTypeAs {};

template <>
struct MobTypeAs<KnightStranger> {
	static constexpr int asInt = static_cast<int>(enumMobType::KnightStranger);
	static constexpr std::string asString = "KnightStranger";
};

template <>
struct MobTypeAs<Elf> {
	static constexpr int asInt = static_cast<int>(enumMobType::Elf);
	static constexpr std::string asString = "Elf";
};

template <>
struct MobTypeAs<Dragon> {
	static constexpr int asInt = static_cast<int>(enumMobType::Dragon);
	static constexpr std::string asString = "Dragon";
};

class MobTypeCvt {
private:
	static std::map<enumMobType, std::string> enum2String;
	static std::map<std::string, enumMobType> string2Enum;
public:
	static std::string to_string(enumMobType type);

	static enumMobType to_enum(std::string type);
};

inline std::map<enumMobType, std::string> MobTypeCvt::enum2String{
	{enumMobType::BaseMob, "BaseMob"},
	{enumMobType::KnightStranger, "KnightStranger"},
	{enumMobType::Elf, "Elf"},
	{enumMobType::Dragon, "Dragon"}
};

inline std::map<std::string, enumMobType> MobTypeCvt::string2Enum{
	{"BaseMob", enumMobType::BaseMob},
	{"KnightStranger", enumMobType::KnightStranger},
	{"Elf", enumMobType::Elf},
	{"Dragon", enumMobType::Dragon}
};

#endif // MOB_H_