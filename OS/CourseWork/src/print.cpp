#include "print.hpp"

print::~print()
{
	static std::mutex mutex;
	std::unique_lock<std::mutex> lock(mutex);

	std::cout << str();
}

print& print::operator<<(pt::ptree data)
{
	pt::write_json(*this, data);

	return *this;
}

printErr::~printErr()
{
	static std::mutex mutex;
	std::unique_lock<std::mutex> lock(mutex);

	std::cerr << str();
}

printLog::~printLog() {
	static std::mutex mutex;
	std::unique_lock<std::mutex> lock(mutex);

	std::cout << "[Log] " << str();
}
