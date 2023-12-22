#include "print.hpp"

print::~print()
{
	static std::mutex mutex;
	std::unique_lock<std::mutex>(mutex);

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
	std::unique_lock<std::mutex>(mutex);

	std::cerr << str();
}
