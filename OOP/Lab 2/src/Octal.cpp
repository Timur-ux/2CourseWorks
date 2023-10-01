#include "Octal.hpp"

int to10SS(Octal & octal);
Octal to8CC(int n);

Octal::Octal(initializer_list<unsigned char> n)
{
    if(n.size() > MAXBUFFSIZE) {
        string error = string("Octal should be ")
                     + to_string(MAXBUFFSIZE) 
                     + string(" digits max");

        throw out_of_range(error);
    }

    int j = 0;

    for(auto it = prev(n.end()); j < n.size(); --it, ++j) {
        if(not(*it >= (unsigned char)'0' and *it < (unsigned char)'8')) {
            throw invalid_argument("Representation of octal number must contain only octal digits");
        }

        buff[j] = *it;
    }

    _size = n.size();
}

Octal::Octal(const string &s)
{
    if(s.size() > MAXBUFFSIZE) {
        string error = string("Octal should be ") 
                     + to_string(MAXBUFFSIZE) 
                     + string(" digits max");
        throw out_of_range(error);
    }

    for(int i = s.size()-1, j = 0; i >= 0; --i, ++j) {
        if(not(s[i] >= '0' and s[i] < '8')) {
            throw invalid_argument("Representation of octal number must contain only octal digits");
        }

        buff[j] = s[i];
    }
    _size = s.size();
}

Octal::Octal(const Octal &other) noexcept
{
    _size = other._size;
    for(int i = 0; i < _size; ++i) {
        buff[i] = other.buff[i];
    }
}

Octal::Octal(Octal &&other) noexcept
{
    buff = other.buff;
    _size = other._size;

    other.buff = nullptr;
    other._size = 0;
}

Octal::~Octal()
{
    delete[] buff;
}

bool Octal::operator=(const string &s)
{
    Octal &&temp(s);

    _size = temp._size;
    buff = temp.buff;

    temp._size = 0;
    temp.buff = nullptr;

    return true;
}

bool Octal::operator=(const Octal &rhs)
{
    Octal && temp(rhs.toString());

    _size = temp._size;
    buff = temp.buff;

    temp._size = 0;
    temp.buff = nullptr; 
    return true;
}

bool Octal::operator=(Octal &&rhs)
{
    _size = rhs._size;
    buff = rhs.buff;

    rhs._size = 0;
    rhs.buff = nullptr;
    return true;
}

bool Octal::operator==(const Octal &rhs) const
{
    return toString() == rhs.toString();
}

bool Octal::operator>(const Octal &rhs) const
{
    if(_size != rhs._size) {
        return _size > rhs._size;
    }
    for(int i = _size; i >= 0; --i) {
        if(buff[i] != rhs.buff[i]) {
            return buff[i] > rhs.buff[i];
        }
    }
    return false;
}

bool Octal::operator<(const Octal &rhs) const
{
    return not(*this == rhs) and not(*this > rhs);
}

Octal Octal::operator+(Octal &rhs)
{
    return to8CC(to10SS(*this) + to10SS(rhs));
}

Octal Octal::operator-(Octal &rhs)
{
    return to8CC(to10SS(*this) - to10SS(rhs));
}

string Octal::toString() const
{
    string result = string((char*)buff);
    reverse(result.begin(), result.end());
    return result;
}

size_t Octal::serialize(ostream &os)
{
    auto startPos = os.tellp();

    os << toString() << endl;
    
    return static_cast<size_t>(os.tellp() - startPos);
}

size_t Octal::deserialize(istream &is)
{
    string readedNum;
    auto startPos = is.tellg();

    is >> readedNum;
    *this = readedNum;
    
    return static_cast<size_t>(is.tellg() - startPos);
}

ostream & operator<<(ostream &os, Octal & octal) {
    os << octal.toString();
    
    return os;
}

istream & operator>>(istream &is, Octal &octal) {
    string readedNum;
    is >> readedNum;
    
    octal = readedNum;
    
    return is;
}

int to10SS(Octal & octal) {
    string s = octal.toString();
    int result = 0;
    for(unsigned char c : s) {
        result = result * 8 + (c - (unsigned char)'0');
    }
    return result;
}

Octal to8CC(int n) {
    if(n < 0) {
        return Octal("0");
    }
    string result = "";
    while(n > 0) {
        result = to_string(n%8) + result;
        n /= 8;
    }
    return Octal{result};
}