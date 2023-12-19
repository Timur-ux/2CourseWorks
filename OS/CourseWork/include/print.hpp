#ifndef PRINT_H_
#define PRINT_H_

#include <iostream>
#include <sstream>
#include <mutex>

class print : public std::stringstream {
public:
	~print();
};

class printErr : public std::stringstream {
public:
	~printErr();
};

#endif