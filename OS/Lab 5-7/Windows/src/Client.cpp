#include "Client.hpp"

#include <sstream>
#include <iostream>

Client::Client(std::string servIP, unsigned short servPort)
{
	int errState;

	errState = WSAStartup(MAKEWORD(SOCKET_VERSION_MINOR, SOCKET_VERSION_MAJOR), &wsData);
	if (errState != 0) {
		std::stringstream errorStream;
		errorStream << "Error: WinSock version initialization failed #" << WSAGetLastError();
		throw std::invalid_argument(errorStream.str());
	}

	in_addr ipToNum;
	errState = inet_pton(AF_INET, (PCSTR)servIP.c_str(), &ipToNum);
	if (errState <= 0) {
		std::stringstream errorStream;
		errorStream << "Error: IP translation to specific numeric format failed #" << WSAGetLastError();
		throw std::invalid_argument(errorStream.str());
	}

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET) {
		std::stringstream errorStream;
		errorStream << "Error: socket initialization failed #" << WSAGetLastError();
		throw std::invalid_argument(errorStream.str());
	}

	sockaddr_in servInfo;
	ZeroMemory(&servInfo, sizeof(servInfo));

	servInfo.sin_family = AF_INET;
	servInfo.sin_addr = ipToNum;
	servInfo.sin_port = htons(servPort);

	errState = connect(clientSocket, (sockaddr*)&servInfo, sizeof(servInfo));

	if (errState != 0) {
		std::stringstream errorStream;
		errorStream << "Error: socket connection to server failed #" << WSAGetLastError();
		throw std::invalid_argument(errorStream.str());
	}
}

Client::~Client()
{
	if (clientSocket) {
		closesocket(clientSocket);
	}

	WSACleanup();
}

void Client::sendData(std::vector<char> data)
{
	data.resize(MESSAGE_BUFFER_SIZE, '\0');

	int packetSize = send(clientSocket, data.data(), data.size(), 0);

	if (packetSize == SOCKET_ERROR) {
		std::cerr << "Warning: sending data to server failed #" << WSAGetLastError() << std::endl;
	}
}

std::vector<char> Client::recieve()
{
	std::vector<char> result(MESSAGE_BUFFER_SIZE);

	int packetSize = recv(clientSocket, result.data(), result.size(), 0);

	if (packetSize == SOCKET_ERROR) {
		std::stringstream errorStream;
		errorStream << "Warning: recieving data from server failed #" << WSAGetLastError();
		throw std::runtime_error(errorStream.str());
	}

	return result;
}
