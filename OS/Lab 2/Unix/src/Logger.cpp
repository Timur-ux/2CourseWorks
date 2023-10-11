#include "Logger.hpp"



Logger::Logger(string fileName,  OpenMode mode, string header)
{
    if(mode == ADD) { 
        file.open(fileName, ios::out | ios::app);
    }
    else if( mode == NEW) {
        file.open(fileName, ios::out);
        write(header);
    }
}

Logger::~Logger() {
    file.close();
}

void Logger::write(string line)
{
    file << line << endl;
}

