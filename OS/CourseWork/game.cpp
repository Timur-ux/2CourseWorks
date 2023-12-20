#include "Network/GameServer.hpp"
#include <iostream>

#include <boost/property_tree/ptree.hpp>

namespace pt = boost::property_tree;

int main(int argc, char* argw[]) {
	if (argc != 3) {
		throw std::invalid_argument("Usage: <program name> <IP adress> <free port>");
	}
	
	std::string IP = argw[1];
	unsigned short port = atoi(argw[2]);

	GameServer server();



	return 0;
}