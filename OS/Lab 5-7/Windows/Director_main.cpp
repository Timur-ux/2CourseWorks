#include <iostream>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

#include "SocketManager.hpp"
#include "Director.hpp"
#include "Worker.hpp"
#include "MessageQueue.hpp"

#pragma comment(lib, "Ws2_32.lib")

MessageQueue messageQueue;
void listener();
void sender();
void reciever();

int main(int argc, const char* argw[]) {
	std::string defaultIP = "127.0.0.1";
	const int defaultPort = 1234;
	
	std::string IP = defaultIP;
	unsigned short port = defaultPort;

	if (argc == 3) {
		IP = argw[1];
		port = atoi(argw[2]);
	}
	
	SocketResourceManager resourceManager;

	if (resourceManager.socketStartup() != 0) {
		int errCode = WSAGetLastError();
		throw std::runtime_error("Error: WinSock version initialization failed #"
			+ std::to_string(errCode));
	}

	SOCKET socket = resourceManager.createSocket();

	if (socket == INVALID_SOCKET) {
		int errCode = WSAGetLastError();
		throw std::runtime_error("Error: socket creating failed #" 
			+ std::to_string(errCode));
	}

	in_addr ipAsNum;
	if (ipToNum(IP, &ipAsNum) <= 0) {
		throw std::runtime_error("Error: IP translation to special numeric format failed");
	}

	int errCode = bindToFreePort(&socket, &ipAsNum, &port) != 0;
	if (errCode != 0) {
		throw std::runtime_error("Error: Binding socket with server info failed #"
			+ std::to_string(WSAGetLastError()));
	}


}

