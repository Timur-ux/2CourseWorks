#include "Octal.hpp"

Octal::Octal(const string &s)
{
    if(s.size() > MAXBUFFSIZE) {
        string error = string("Octal should be ") + string(MAXBUFFSIZE) + string(" digits max");
        throw out_of_range(error);
    }

    for(int i = s.size()-1, j = 0; i >= 0; ++i, ++j) {
        if(not(s[i] >= '0' and s[i] < '8')) {
            throw invalid_argument("String representation of octal number must contain only octal digits");
        }

        buff[j] = s[i];
    }
}

Octal::Octal(int n)
{
    for(int i = 0; n > 0; ++i) {
        if(i > MAXBUFFSIZE) {
            string error = string("Octal should be ") + string(MAXBUFFSIZE) + string(" digits max");
            throw out_of_range(error);
        }

        int cur = n % 10;

        if(cur >= 8) {
            throw invalid_argument("String representation of octal number must contain only octal digits");
        }

        buff[i] = cur;
        n /= 10;
    }
}

Octal::~Octal()
{
    free(buff);
}

bool Octal::operator=(const string &s)
{
    for(char c)
}

bool Octal::operator=(int n)
{
    return false;
}

bool Octal::operator=(Octal &rhs)
{
    return false;
}

bool Octal::operator==(const Octal &rhs)
{
    return false;
}

bool Octal::operator>(const Octal &rhs)
{
    return false;
}

bool Octal::operator<(const Octal &rhs)
{
    return false;
}

Octal Octal::operator+(Octal &rhs)
{
    return Octal();
}

Octal Octal::operator-(Octal &rhs)
{
    return Octal();
}

Octal Octal::copy()
{
    return Octal();
}
