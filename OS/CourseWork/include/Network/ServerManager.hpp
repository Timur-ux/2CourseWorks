#ifndef SERVER_MANAGER_H_
#define SERVER_MANAGER_H_

#include "interfaces/IServer.hpp"
#include "Messages/MessageVisitor.hpp"
#include "Messages/concretMessages/allConcretMessages.hpp"
#include "print.hpp"

#include <map>

class ServerManager : public message::ISubscriber
	, message::request::IMessageVisitor {
private:
	network::IServer& server;
	std::map<long long, std::string> clients;
public:
	ServerManager(network::IServer& _server) : server(_server) {}

	void subscribeTo(message::IObserver*) override;
	void notify(message::request::IMessage) override;

	void visit(message::request::IAuth&) override;
	void visit(message::request::IPing& message) override;
	void visit(message::request::IGetLogins& message) override;
	void visit(message::request::ICreateNewGame& message) override;
};

#endif // !SERVER_MANAGER_H_
