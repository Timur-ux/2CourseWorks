#include "Server.hpp"
#include <sstream>
#include <iostream>

Server::Server(std::string IP, unsigned short port)
{
	int errStat;

	// ip to specific numeric format
	in_addr ipToNum;
	errStat = inet_pton(AF_INET, IP.c_str(), &ipToNum);
	if (errStat <= 0) {
		throw std::runtime_error("Error: IP translation to specific numeric format failed");
	}

	// WinSocket version initialization
	errStat = WSAStartup(MAKEWORD(SOCKET_VERSION_MINOR, SOCKET_VERSION_MAJOR), &wsData);
	if (errStat != 0) {
		std::stringstream errorStream;
		errorStream << "Error: WinSock version initialization failed #" << WSAGetLastError();
		throw std::runtime_error(errorStream.str());
	}

	// create server socket
	servSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (servSocket == INVALID_SOCKET) {
		std::stringstream errorStream;
		errorStream << "Error: server socket initialization failed #" << WSAGetLastError();
		throw std::runtime_error(errorStream.str());
	}

	// binding server socket
	ZeroMemory(&servInfo, sizeof(servInfo));
	servInfo.sin_family = AF_INET;
	servInfo.sin_addr = ipToNum;
	servInfo.sin_port = htons(port);

	errStat = bind(servSocket, (sockaddr*)&servInfo, sizeof(servInfo));
	if (errStat != 0) {
		std::stringstream errorStream;
		errorStream << "Error: binding server socket to server info failed #" << WSAGetLastError();
		throw std::runtime_error(errorStream.str());
	}
}

Server::~Server()
{
	if (servSocket) {
		closesocket(servSocket);
	}

	for (auto& elem : clients) {
		closesocket(elem.first);
	}

	WSACleanup();
}

void Server::startListen()
{
	int errStat;
	errStat = listen(servSocket, SOMAXCONN);
	if (errStat != 0) {
		std::stringstream errorStream;
		errorStream << "Error: socket listening failed #" << WSAGetLastError();
		throw std::runtime_error(errorStream.str());
	}

	isNowListening = true;
	while (isNowListening) {
		sockaddr_in clientInfo;
		ZeroMemory(&clientInfo, sizeof(clientInfo));
		int clientInfoSize = sizeof(clientInfo);

		SOCKET clientSocket = accept(servSocket, (sockaddr*)&clientInfo, &clientInfoSize);

		if (clientSocket == INVALID_SOCKET) {
			std::cerr << "Warning: client detected but can't connect to a client #" << WSAGetLastError() << std::endl;
		}

		clients[clientSocket] = clientInfo;
		lastClient = clientSocket;
	}
}

void Server::sendTo(SOCKET client, std::vector<char> data)
{
	data.resize(MESSAGE_BUFFER_SIZE, '\0');
	int packetSize = 0;

	packetSize = send(client, data.data(), data.size(), 0);
	if (packetSize == SOCKET_ERROR) {
		std::cerr << "Warning: sending message to client failed #" << WSAGetLastError();
	}
}

std::vector<char> Server::recieveFrom(SOCKET client)
{
	if (clients.find(client) == clients.end()) {
		std::cerr << "Warning: can't recieve message from unconnected client" << std::endl;
		return {};
	}
	int packetSize = 0;
	std::vector<char> data(MESSAGE_BUFFER_SIZE);

	packetSize = recv(client, data.data(), data.size(), 0);

	if (packetSize == SOCKET_ERROR) {
		std::cerr << "Warning: recieving message from client failed #" << WSAGetLastError() << std::endl;
		return {};
	}

	{
		std::unique_lock<std::mutex> lock(mqMutex);
		mqRecieved.push(Message{ client, servSocket, data });
	}
	return data;
}
