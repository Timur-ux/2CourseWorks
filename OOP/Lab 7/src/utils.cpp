#include "utils.hpp"
#include <cmath>

std::string replace(std::string src, char from, char to) {
    for (char & c : src) {
        if (c == from) {
            c = to;
        }
    }

    return src;
}

double mathMod(double val, double mod) {
    return std::fmod(val, mod);
}