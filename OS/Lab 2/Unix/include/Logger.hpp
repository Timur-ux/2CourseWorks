#pragma once

#include <fstream>
#include <stdexcept>

using namespace std;

typedef enum {NEW, ADD} OpenMode;

class Logger {
private:
    string fileName;
    ofstream file;
public:
    Logger(string fileName, OpenMode mode = ADD, string header = " ");
    
    void write(string line);
    ~Logger();
};