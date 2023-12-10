#ifndef PRINT_H_
#define PRINT_H_

#include <iostream>
#include <sstream>
#include <mutex>

class print : public std::stringstream {
	static std::mutex mutex;
public:
	~print() {
		std::unique_lock<std::mutex>(mutex);

		std::cout << str();
	}
};

#endif