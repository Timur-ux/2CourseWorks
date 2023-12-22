#include <iostream>
#include <vector>

#include "Server.hpp"


int main(int argc, char* argw[]) {
	if (argc != 5) {
		throw std::invalid_argument("Usage <program name> <server IP> <free port>");
	}

	std::string IP(argw[1]);
	unsigned short port = atoi(argw[2]);
	std::vector<unsigned short> ports{port, port + 1, port + 2};

	Server server(IP, ports);
}