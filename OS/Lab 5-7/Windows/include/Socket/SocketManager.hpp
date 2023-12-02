#ifndef SOCKET_MANAGER_H_
#define SOCKET_MANAGER_H_

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdexcept>
#include <string>
#include <list>

const short int BUFF_SIZE = 1024;

const int SOCKET_VERSION_MIN = 2;
const int SOCKET_VERSION_MAX = 2;

int addressFamily = AF_INET;
int socketType = SOCK_STREAM;

int ipToNum(std::string ip, in_addr* addrBuf);
int bindSocket(SOCKET socket, in_addr* ipAddr, unsigned short port);
int bindToFreePort(SOCKET socket, in_addr* ipAddr, unsigned short* basePort);

struct SocketResourceManager {
	static WSADATA wsData;

	std::list<SOCKET> openedSockets;

	int socketStartup();
	SOCKET createSocket();
	void addSocketToManager(SOCKET socket);

	~SocketResourceManager();
};

#endif