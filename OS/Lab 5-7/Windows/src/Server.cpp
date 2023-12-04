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

MessageQueue<Message>& Server::getRecievedMessages()
{
	return mqRecieved;
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
		notify_all(clientSocket);
	}
}

void Server::stopListen()
{
	isNowListening = false;
}

void Server::sendTo(SOCKET client, std::vector<char> data)
{
	data.resize(MESSAGE_BUFFER_SIZE, '\0');
	int packetSize = 0;

	packetSize = send(client, data.data(), data.size(), 0);
	if (packetSize == SOCKET_ERROR) {
		std::cerr << "Warning: sending message to client failed #" << WSAGetLastError() << std::endl;
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

	mqRecieved.push(Message{ client, servSocket, data });
	return data;
}

void Server::subscribe(ISockSubscriber* subscriber)
{
	subscribers.emplace_back(subscriber);
}

void Server::notify_all(SOCKET socket)
{
	for (auto subscriber : subscribers) {
		subscriber->update(socket);
	}
}

std::vector<SOCKET> Server::chekAndGetDeadSockets(long waitTime_sec, long waitTime_microsec)
{
	if (clients.size() == 0) {
		return {};
	}

	std::vector<SOCKET> deadsockets;

	int i = 0;
	fd_set socketsSet;
	FD_ZERO(&socketsSet);

	if (clients.size() > FD_SETSIZE) {
		std::cerr << "Warning: clients quantity more than fd_set limit: " << FD_SETSIZE << std::endl;
	}

	for (auto& client : clients) {
		SOCKET currentSocket = client.first;
		FD_SET(currentSocket, &socketsSet);
	}
	
	TIMEVAL timeval;
	timeval.tv_sec = waitTime_sec;
	timeval.tv_usec = waitTime_microsec;

	int goodSockets = select(
		NULL
		, NULL
		, NULL
		, &socketsSet
		, &timeval
	);

	if (goodSockets == SOCKET_ERROR) {
		std::stringstream errorStream;
		errorStream << "Error: select failed #" << WSAGetLastError();
		throw std::runtime_error(errorStream.str());
	}

	if (goodSockets == 0) {
		std::cerr << "Warning: select's timelimit expired" << std::endl;
	}

	for (auto& client : clients) {
		SOCKET currentSocket = client.first;

		if (!FD_ISSET(currentSocket, &socketsSet)) {
			deadsockets.push_back(currentSocket);
		}
	}

	return deadsockets;
}
