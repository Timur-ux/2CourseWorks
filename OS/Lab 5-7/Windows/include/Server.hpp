#ifndef SERVER_H_
#define SERVER_H_

#include <map>
#include <string>
#include <stdexcept>
#include <shared_mutex>
#include <vector>
#include <zmq.hpp>

#include "bufferSize.hpp"
#include "Observer.hpp"
#include "print.hpp"

#pragma comment(lib, "Ws2_32.lib")

constexpr int SOCKET_VERSION_MINOR = 2;
constexpr int SOCKET_VERSION_MAJOR = 2;

struct Message {
	int clientId;
	int messageNumber;
	char message[MESSAGE_BUFFER_SIZE];
};

struct ClientInfo {
	SOCKET socket;
	sockaddr_in addr;
	long long id = 0;
};

struct ListenData {
	bool isNowListening = false;
};

struct RecievingData {
	bool isNowRecieving;
	long waitSec = 0;
	long waitMicroSec = 300000;
};

class Server : public ISockObserver, public ISockSubscriber {
private:
	WSADATA wsData;
	void* context;
	void* servSocket;

	std::map<SOCKET, ClientInfo> clients;

	ListenData listenData;
	RecievingData recievingData;

	std::vector<ISockSubscriber*> subscribers;
	std::shared_mutex servMutex;
public:
	Server(std::string IP, unsigned short port);
	~Server();

	void startListen();
	void stopListen();
	void startRecieving();
	void stopRecieving();

	void sendTo(SOCKET client, std::vector<char> data);
	void recieveFrom(SOCKET client);
	void disconnectClient(SOCKET client);

	void subscribe(ISockSubscriber* subscriber) override;
	void notify_all(ObserverData data) override;

	void update(ObserverData data) override;

	std::vector<SOCKET> chekAndGetDeadSockets(long waitTime_sec = 1, long waitTime_microsec = 0);

	ClientInfo getClientInfoBySocket(SOCKET socket);
};

#endif // !SERVER_H_
