#include "print.hpp"

print::~print()
{
	static std::mutex mutex;
	std::unique_lock<std::mutex>(mutex);

	std::cout << str();
}

printErr::~printErr()
{
	static std::mutex mutex;
	std::unique_lock<std::mutex>(mutex);

	std::cerr << str();
}
