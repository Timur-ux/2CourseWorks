#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <ext/stdio_filebuf.h>
using namespace std;

class PipeStream {
    private: 
    __gnu_cxx::stdio_filebuf<char> inputFBuff;
    __gnu_cxx::stdio_filebuf<char> outputFBuff;
    ostream outStream;
    istream inStream;
    public:
        PipeStream(int outputFD, int inputFD) : inputFBuff(inputFD, ios_base::in), outputFBuff(outputFD, ios_base::out), 
        outStream(&outputFBuff), inStream(&inputFBuff) {}
        void write(const string& str);
        string read();
};