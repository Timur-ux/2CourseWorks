#include "MyLogger.hpp"

MyLogger::MyLogger(string fileName, string header)
{
    if(header != "") { // If headers aren't gived we append data
        file.open(fileName, ios::out | ios::app);
    }
    else { // else open clear file and write header
        file.open(fileName, ios::in);
        write(header);
    }
}

// MyLogger::MyLogger(MyLogger &&other)
// {
//     fileName = other.fileName;
//     file = other.file;
// }

// void MyLogger::operator=(MyLogger &&other)
// {
//     fileName = other.fileName;
//     file = other.file;
// }

MyLogger::~MyLogger() {
    file.close();
}

void MyLogger::write(string line)
{
    file << line << endl;
}

