#include "Location.hpp"

std::istream & operator>>(std::istream & is, Position & pos) {
	is >> pos.x >> pos.y;

	return is;
}
