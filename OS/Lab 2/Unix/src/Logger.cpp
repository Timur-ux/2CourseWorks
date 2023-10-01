#include "Logger.hpp"

Logger::Logger(string fileName, string header)
{
    if(header != "") { // If headers aren't gived we append data
        file.open(fileName, ios::out | ios::app);
    }
    else { // else open clear file and write header
        file.open(fileName);
        write(header);
    }
}

~Logger() {
    file.close();
}

void Logger::write(string line)
{
    file << line << endl;
}

