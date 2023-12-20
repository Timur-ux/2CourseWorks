#ifndef SOCKET_H_
#define SOCKET_H_

struct Socket {
	std::string IP;
	unsigned short port;

	Socket(std::string _IP, unsigned short _port) : IP(_IP), port(_port) {}
};

#endif