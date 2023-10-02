#pragma once

#include <fstream>
#include <stdexcept>

using namespace std;

class MyLogger {
private:
    string fileName;
    ofstream file;
public:
    MyLogger(string fileName, string header = "");
    
    void write(string line);
    ~MyLogger();
};