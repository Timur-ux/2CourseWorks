#include "utils.hpp"

std::string replace(std::string src, char from, char to) {
	for (char & c : src) {
		if (c == from) {
			c = to;
		}
	}

	return src;
}