#ifndef SERVER_MESSAGE_MANAGER_H_
#define SERVER_MESSAGE_MANAGER_H_

#include "Server.hpp"
#include "Messages/MessageManager.hpp"

class ServerMessageManager : public IMessageManager {
private:
	Server* server = nullptr;
public:
	void push(pt::ptree data) override;
	
	void setServer(Server * server);
};

#endif // !SERVER_MESSAGE_MANAGER_H_
