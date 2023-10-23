#pragma once

#include <iostream>

using namespace std;

class Serializible {
public:
    virtual size_t serialize(ostream & os) = 0;
    virtual size_t deserialize(istream & is) = 0;
};