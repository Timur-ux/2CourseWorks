#ifndef IO_MANAGER_H_
#define IO_MANAGER_H_

#include <string>
#include <sstream>
#include <memory>
#include "Location.hpp"

class DangeonRedactor {
private:
	IObserver logObserver;
	std::shared_ptr<ILocation> dangeonLocation;
public:
	void inputCommand(std::string command) {
		std::stringstream commandStream;
		int commandType;
		std::string commandArg;

		commandStream >> commandType;

		switch (commandType) {
			// case 1:
			// 	command1();
			// 	break;
			// case 2:
			// 	command1();
			// 	break;
			//...
		}
	}

	void addMob()
};

#endif // IO_MANAGER_H_