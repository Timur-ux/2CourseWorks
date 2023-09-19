#include "PipeStream.hpp"

void PipeStream::write(const string &str)
{
    if(!outStream.good()) {
        cerr << "ERROR: PipeStream write failed" << endl;
    }
    outStream << str;
    return;
}

string PipeStream::read()
{
    if(!inStream.good()) {
        cerr << "ERROR: PipeStream read failed" << endl;
    }
    string str;
    getline(inStream, str);
    return str;
}
