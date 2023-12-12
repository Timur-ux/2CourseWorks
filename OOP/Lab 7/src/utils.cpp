#include "utils.hpp"
#include <cmath>
#include <cstdlib>

std::string replace(std::string src, char from, char to) {
    for (char & c : src) {
        if (c == from) {
            c = to;
        }
    }

    return src;
}

double mathMod(double val, double mod) {
    double result = std::fmod(val, mod);
    if (result < 0) {
        result += mod;
    }

    return result;
}

GameCube::GameCube() {
    throwCube();
}

void GameCube::throwCube() {
    value = rand() % 6 + 1;
}

int GameCube::getValue() const {
    return value;
}

print::~print() {
    static std::mutex mutex;

    std::lock_guard<std::mutex> lock(mutex);

    std::cout << str();
}
