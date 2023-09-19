#pragma once

#include <stdexcept>
#include <string>

using namespace std;

class Octal {
private:
    const int MAXBUFFSIZE = 30;
    unsigned char buff[MAXBUFFSIZE];  
    string get();
public:
    Octal() = default();
    Octal(const string & s);
    Octal(int n);
    
    ~Octal();

    bool operator=(const string & s);
    bool operator=(int n);
    bool operator=(Octal &rhs);

    bool operator==(const Octal &rhs);
    bool operator>(const Octal &rhs);
    bool operator<(const Octal &rhs);

    Octal operator+(Octal &rhs);
    Octal operator-(Octal &rhs);
    Octal copy();

}