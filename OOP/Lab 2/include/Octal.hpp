#pragma once

#include <string>
#include <iostream>

using namespace std;

class Octal {
private:
    const int MAX_BUFF_SIZE = 30;
    unsigned char buff[MAX_BUFF_SIZE];
public:
    Octal() = default;
    Octal(const string & str);
    Octal(int n);

    void operator=(Octal & rhs);
    void operator=(const string & rhs);
    void operator=(int n);

    Octal operator+(Octal & rhs);
    Octal operator-(Octal & rhs);
    Octal copy();

    bool operator==(Octal & rhs);
    bool operator>(Octal & rhs);
    bool operator<(Octal & rhs);

}