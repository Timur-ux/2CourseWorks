#ifndef DIRECTOR_H_
#define DIRECTOR_H_

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include "Topology.hpp"

struct Data;
struct WorkerInfo;
class Director {
private:
	Topology::BinTree<WorkerInfo> topology;
public:
	Director() = default;
	void create(long id, long parent);
	void kill(long id);
	void exec(long id, Data data);
};


struct WorkerInfo {
	SOCKET socket;

	WorkerInfo(SOCKET _socket) : socket(_socket) {}
};
#endif // !DIRECTOR_H_
