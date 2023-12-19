#include <iostream>
#include <vector>

#include "Server.hpp"


int main(int argc, char* argw[]) {
	if (argc != 5) {
		throw std::invalid_argument("Usage <program name> <server IP> <free port 1> <free port 2> <free port 3>");
	}

	std::string IP(argw[1]);

	std::vector<unsigned short> ports{atoi(argw[2]), atoi(argw[3]), atoi(argw[4])};

	Server server(IP, ports);
}