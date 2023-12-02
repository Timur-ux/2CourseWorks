#include "Socket/SocketManager.hpp"


int SocketResourceManager::socketStartup()
{
	return WSAStartup(MAKEWORD(
		SOCKET_VERSION_MIN
		, SOCKET_VERSION_MAX
	), &wsData);
}

SOCKET SocketResourceManager::createSocket()
{
	SOCKET socket = socket(addressFamily, socketType, 0);
	openedSockets.push_back(socket);
	
	return socket;
}

void SocketResourceManager::addSocketToManager(SOCKET socket)
{
	openedSockets.push_back(socket)
}

SocketResourceManager::~SocketResourceManager()
{
	while (!openedSockets.empty()) {
		auto socketIt = std::begin(openedSockets);
		closesocket(*socketIt);
		openedSockets.erase(socketIt);
	}

	WSACleanup();
}

int ipToNum(std::string ip, in_addr* addrBuff)
{
	return inet_pton(addressFamily, ip.c_str(), addrBuff);
}

int bindSocket(SOCKET socket, in_addr* ipAddr, unsigned short port)
{
	sockaddr_in socketInfo;
	ZeroMemory(&socketInfo, sizeof(socketInfo));

	socketInfo.sin_family = addressFamily;
	socketInfo.sin_addr = *ipAddr;
	socketInfo.sin_port = htons(port);
	
	return bind(socket, (sockaddr*)&socketInfo, sizeof(socketInfo));
}

int bindToFreePort(SOCKET socket, in_addr* ipAddr, unsigned short* basePort)
{ // Find free port from basePort given and bind to it. Set *basePort to founded binded port
	int errCode = bindSocket(socket, ipAddr, *basePort);
	while (errCode == WSAEADDRINUSE) {
		++(*basePort);
		errCode = bindSocket(socket, ipAddr, *basePort);
		
		if (*basePort == (unsigned short)(-1) and errCode == WSAEADDRINUSE) {
			throw std::runtime_error("There are not free ports");
		}
	}

	return errCode;
}
