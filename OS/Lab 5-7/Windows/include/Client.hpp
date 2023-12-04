#ifndef CLIENT_H_
#define CLIENT_H_

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <stdexcept>
#include <vector>

#include "bufferSize.hpp"

#pragma comment(lib, "Ws2_32.lib")

const int SOCKET_VERSION_MINOR = 2;
const int SOCKET_VERSION_MAJOR = 2;

class Client {
private:
	WSADATA wsData;
	SOCKET clientSocket = 0;
public:
	Client(std::string servIP, unsigned short servPort);
	~Client();

	void sendData(std::vector<char> data);
	std::vector<char> recieve();
};

#endif // !CLIENT_H_
