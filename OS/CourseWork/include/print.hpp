#ifndef PRINT_H_
#define PRINT_H_

#include <iostream>
#include <sstream>
#include <mutex>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace pt = boost::property_tree;

class print : public std::stringstream {
public:
	~print();
};

class printErr : public std::stringstream {
public:
	~printErr();
};

class printLog : public std::stringstream {
public:
	~printLog();
};
#endif