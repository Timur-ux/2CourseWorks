#ifndef SERVER_H_
#define SERVER_H_

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <map>
#include <string>
#include <stdexcept>
#include <queue>
#include <mutex>
#include <vector>

#include "bufferSize.hpp"

#pragma comment(lib, "Ws2_32.lib")

constexpr int SOCKET_VERSION_MINOR = 2;
constexpr int SOCKET_VERSION_MAJOR = 2;

struct Message {
	SOCKET sender;
	SOCKET reciever;
	std::vector<char> data;
};

class Server {
private:
	WSADATA wsData;
	SOCKET servSocket = NULL;
	sockaddr_in servInfo;

	std::map<SOCKET, sockaddr_in> clients;
	std::queue<Message> mqRecieved;
	std::mutex mqMutex;

	bool isNowListening = false;
	SOCKET lastClient = 0;
public:
	Server(std::string IP, unsigned short port);
	~Server();

	void startListen();
	void sendTo(SOCKET client, std::vector<char> data);
	std::vector<char> recieveFrom(SOCKET client);
};

#endif // !SERVER_H_
