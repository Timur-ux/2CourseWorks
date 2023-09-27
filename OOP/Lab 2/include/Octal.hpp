#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include "Serializible.hpp"

using namespace std;

class Octal : public Serializible {
private:
    const int MAXBUFFSIZE{30};
    unsigned char *buff = new unsigned char[MAXBUFFSIZE]{'\0'};  
    size_t _size{0};
public:
    Octal() = default;
    Octal(const initializer_list<unsigned char> n);
    Octal(const string & s);
    
    Octal(const Octal & other) noexcept;
    Octal(Octal && other) noexcept;
    
    ~Octal() noexcept;

    bool operator=(const string & s);
    bool operator=(const Octal &rhs);
    bool operator=(Octal && rhs);

    bool operator==(const Octal &rhs) const;
    bool operator>(const Octal &rhs) const;
    bool operator<(const Octal &rhs) const;

    Octal operator+(Octal &rhs);
    Octal operator-(Octal &rhs);

    string toString() const;

    size_t serialize(ostream & os) override;
    size_t deserialize(istream & is) override;
};

ostream & operator<<(ostream &os, Octal & octal);
istream & operator>>(istream &is, Octal &octal);