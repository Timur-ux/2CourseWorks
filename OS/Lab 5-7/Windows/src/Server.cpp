#include "Server.hpp"
#include <sstream>
#include <iostream>

void printCommandWithIdAfterRetStatus(std::string command, long long id);

Server::Server(std::string IP, unsigned short port)
{
	int errStat;

	context = zmq_ctx_new();
	servSocket = zmq_socket(context, ZMQ_REP);

	std::stringstream addrStream;
	addrStream << "tcp://" << IP << ':' << port;

	zmq_bind(servSocket, addrStream.str().c_str());

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

	listenData.isNowListening = true;
	while (listenData.isNowListening) {
		sockaddr_in clientInfo;
		ZeroMemory(&clientInfo, sizeof(clientInfo));
		int clientInfoSize = sizeof(clientInfo);

		SOCKET clientSocket = accept(servSocket, (sockaddr*)&clientInfo, &clientInfoSize);

		if (clientSocket == INVALID_SOCKET) {
			std::cerr << "Warning: client detected but can't connect to a client #" << WSAGetLastError() << std::endl;
		}

		clients[clientSocket] = { clientSocket, clientInfo, 0 };
		notify_all({ clientSocket, 0 });
	}
}

void Server::stopListen()
{
	listenData.isNowListening = false;
}

void Server::sendTo(SOCKET client, std::vector<char> data)
{
	if (clients.find(client) == clients.end()) {
		throw std::invalid_argument("Not Found");
	}
	data.resize(MESSAGE_BUFFER_SIZE, '\0');
	int packetSize = 0;

	packetSize = send(client, data.data(), static_cast<int>(data.size()), 0);
	if (packetSize == SOCKET_ERROR) {
		std::cerr << "Warning: sending message to client failed #" << WSAGetLastError() << std::endl;
	}
}

void Server::recieveFrom(SOCKET client)
{
	if (clients.find(client) == clients.end()) {
		std::cerr << "Warning: can't recieve message from unconnected client" << std::endl;
		return;
	}
	int packetSize = 0;
	std::vector<char> data(MESSAGE_BUFFER_SIZE);

	packetSize = recv(client, data.data(), static_cast<int>(data.size()), 0);

	if (packetSize == SOCKET_ERROR) {
		std::cerr << "Warning: recieving message from client failed #" << WSAGetLastError() << std::endl;
		return;
	}

	printCommandWithIdAfterRetStatus(std::string(data.data()), clients[client].id);
}

void Server::subscribe(ISockSubscriber* subscriber)
{
	subscribers.emplace_back(subscriber);
}

void Server::notify_all(ObserverData data)
{
	for (auto subscriber : subscribers) {
		subscriber->update(data);
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
		, &socketsSet
		, NULL
		, &timeval
	);

	if (goodSockets == SOCKET_ERROR) {
		std::stringstream errorStream;
		errorStream << "Error: select failed #" << WSAGetLastError();
		throw std::runtime_error(errorStream.str());
	}

	for (auto& client : clients) {
		SOCKET currentSocket = client.first;

		if (!FD_ISSET(currentSocket, &socketsSet)) {
			deadsockets.push_back(currentSocket);
		}
	}

	return deadsockets;
}

void Server::update(ObserverData data) {
	if (clients.find(data.socket) == clients.end()) {
		return;
	}

	clients[data.socket].id = data.id;
}

void Server::startRecieving() {
	recievingData.isNowRecieving = true;

	while (recievingData.isNowRecieving) {
		{
			std::shared_lock<std::shared_mutex> lock(servMutex);
			if (clients.size() == 0) {
				continue;
			}
		}

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
		timeval.tv_sec = recievingData.waitSec;
		timeval.tv_usec = recievingData.waitMicroSec;

		int goodSockets = select(
			NULL
			, &socketsSet
			, NULL
			, NULL
			, &timeval
		);

		if (goodSockets == SOCKET_ERROR) {
			std::stringstream errorStream;
			errorStream << "Error: select failed #" << WSAGetLastError();
			throw std::runtime_error(errorStream.str());
		}

		SOCKET badSocket = 0;
		for (auto& client : clients) {
			std::shared_lock<std::shared_mutex> lock(servMutex);
			SOCKET currentSocket = client.first;

			if (FD_ISSET(currentSocket, &socketsSet)) {
				int packetSize = 0;
				std::vector<char> data(MESSAGE_BUFFER_SIZE);

				packetSize = recv(currentSocket, data.data(), static_cast<int>(data.size()), 0);

				if (packetSize == SOCKET_ERROR) {
					int errCode = WSAGetLastError();
					if (errCode == WSAECONNRESET) {
						std::cerr << "Warning: client with Id: " << client.second.id << " was hardly closed" << std::endl;
						badSocket = currentSocket;
						break;
					}
					std::cerr << "Warning: recieving message from client failed #" << WSAGetLastError() << std::endl;
					continue;
				}
				printCommandWithIdAfterRetStatus(std::string(data.data()), clients[currentSocket].id);
			}
		}

		if (badSocket) {
			disconnectClient(badSocket);
		}
	}
}

void Server::disconnectClient(SOCKET client) {
	auto clientIt = clients.find(client);
	if (clientIt != clients.end()) {
		std::unique_lock<std::shared_mutex> lock(servMutex);
		closesocket(client);
		clients.erase(client);
	}
}

void Server::stopRecieving() {
	recievingData.isNowRecieving = false;
}

ClientInfo Server::getClientInfoBySocket(SOCKET socket) {
	if (clients.find(socket) == clients.end()) {
		throw std::invalid_argument("Not found");
	}

	return clients[socket];
}

void printCommandWithIdAfterRetStatus(std::string command, long long id)
{
	std::stringstream dataStream(command);
	std::string returnStatus;

	dataStream >> returnStatus;
	std::stringstream formattedCommand;

	formattedCommand << returnStatus << " : " << id;
	std::string temp;
	bool isFirst = true;
	while (dataStream >> temp) {
		if (isFirst) {
			formattedCommand << " :";
			isFirst = false;
		}

		formattedCommand << ' ' << temp;
	}

	print() << formattedCommand.str() << std::endl;
}
