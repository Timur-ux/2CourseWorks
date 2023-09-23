#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>

using namespace std;

class Octal {
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
    Octal copy() const;

    string get() const;
    size_t size() const;
};