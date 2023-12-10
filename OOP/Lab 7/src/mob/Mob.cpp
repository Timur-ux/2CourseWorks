#include "mob/Mob.hpp"

std::string Mob::getName() const {
	return name;
}

std::ostream & operator<<(std::ostream & os, enumMobType type) {
	os << static_cast<int>(type);

	return os;
}

std::istream & operator>>(std::istream & is, enumMobType & type) {
	int intType;

	is >> intType;
	type = enumMobType{ intType };

	return is;
}

std::string MobTypeCvt::to_string(enumMobType type) {
	return enum2String[type];
}

enumMobType MobTypeCvt::to_enum(std::string type) {
	if (string2Enum.find(type) == string2Enum.end()) {
		throw std::invalid_argument("Undefined type given to MobTypeCvt: " + type);
	}

	return string2Enum[type];
}