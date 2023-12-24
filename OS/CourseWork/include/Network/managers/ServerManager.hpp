#ifndef SERVER_MANAGER_H_
#define SERVER_MANAGER_H_

#include "../interfaces/IServer.hpp"
#include "Messages/MessageVisitor.hpp"
#include "Messages/concretMessages/allConcretMessages.hpp"
#include "Messages/messageFabric/MessageFabric.hpp"
#include "print.hpp"

#include <map>
#include <algorithm>
#include <list>

class ServerManager : public message::ISubscriber
	, public message::IMessageVisitor {
private:
	network::IServer& server;
	std::map<long long, std::string> clients;
	unsigned short freePort = 5000;
public:
	ServerManager(network::IServer& _server) : server(_server) {}

	void subscribeTo(message::IObserver*) override;
	void notify(message::IMessage &) override;

	void visit(message::request::IAuth&) override;
	void visit(message::request::IGetLogins& message) override;
	void visit(message::request::ICreateNewGame& message) override;
};

#endif // !SERVER_MANAGER_H_
