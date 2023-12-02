#ifndef LISTENER_H_
#define LISTENER_H_

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <queue>
#include <memory>

class Listener {
private:
	std::shared_ptr<std::queue<SOCKET>> socketsStore;
public:
	Listener() = default;

	void operator()();
};

#endif // !LISTENER_H_