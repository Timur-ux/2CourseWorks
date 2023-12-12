#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <string>
#include <sstream>
#include <mutex>

std::string replace(std::string src, char from, char to);

double mathMod(double val, double mod);

class GameCube {
private:
    int value;
public:
    GameCube();
    void throwCube();
    int getValue() const;
};

class print : public std::stringstream {
public:
    ~print();
};

#endif
