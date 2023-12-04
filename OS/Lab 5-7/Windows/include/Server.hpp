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
#include "Observer.hpp"
#include "MessageQueue.hpp"

#pragma comment(lib, "Ws2_32.lib")

#define MY_FD_SETSIZE 124

#ifdef MY_FD_SETSIZE
	#define FD_SETSIZE MY_FD_SETSIZE
#endif

constexpr int SOCKET_VERSION_MINOR = 2;
constexpr int SOCKET_VERSION_MAJOR = 2;

struct Message {
	SOCKET sender;
	SOCKET reciever;
	std::vector<char> data;
};

class Server : public ISockObserver {
private:
	WSADATA wsData;
	SOCKET servSocket = NULL;
	sockaddr_in servInfo;

	std::map<SOCKET, sockaddr_in> clients;
	MessageQueue<Message> mqRecieved;

	bool isNowListening = false;

	std::vector<ISockSubscriber*> subscribers;
public:
	Server(std::string IP, unsigned short port);
	~Server();

	MessageQueue<Message>& getRecievedMessages();
	void startListen();
	void stopListen();
	
	void sendTo(SOCKET client, std::vector<char> data);
	std::vector<char> recieveFrom(SOCKET client);

	void subscribe(ISockSubscriber* subscriber) override;
	void notify_all(SOCKET socket) override;

	std::vector<SOCKET> chekAndGetDeadSockets(long waitTime_sec = 1, long waitTime_microsec = 0);
};

#endif // !SERVER_H_
