#ifndef CLIENT_MANAGER_H_
#define CLIENT_MANAGER_H_

#include "../interfaces/IClient.hpp"
#include "Messages/MessageObserver.hpp"
#include "Messages/MessageVisitor.hpp"
#include "Messages/messageFabric/MessageFabric.hpp"

class ClientManager
	: public message::ISubscriber
	, public message::IMessageVisitor {
private:
	long long id = -1;
	std::string login = "Unset";

	network::IClient& client;
public:
	ClientManager(network::IClient& _client) : client(_client) {}
	
	void provideAuth();

	void subscribeTo(message::IObserver*) override;
	void notify(message::IMessage&) override;

	void visit(message::request::IPing&) override;

	void visit(message::reply::IAuth&) override;
	void visit(message::reply::IGetLogins&) override;
	void visit(message::reply::IInviteToGame&) override;
};

#endif // !CLIENT_MANAGER_H_