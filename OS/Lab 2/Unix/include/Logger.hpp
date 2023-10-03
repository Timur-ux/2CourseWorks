#pragma once

#include <fstream>
#include <stdexcept>

using namespace std;

class Logger {
private:
    string fileName;
    ofstream file;
public:
    Logger(string fileName, string header = " ");
    
    void write(string line);
    ~Logger();
};