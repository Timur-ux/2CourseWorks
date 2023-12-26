#ifndef CLIENT_H_
#define CLIENT_H_

#include "../interfaces/IClient.hpp"
#include "../ports.hpp"
#include "Messages/MessageObserver.hpp"
#include "Messages/messageFabric/MessageFabric.hpp"

#include <string>
#include <map>
#include <list>
#include <zmq.hpp>

namespace network {
	class Client 
		: public IClient
		, public message::IObserver {
	private:
		zmq::context_t& context;
		std::string IP;
		std::map<ports, zmq::socket_t> sockets;
		std::map<ports, unsigned short> ports;

		std::list<message::ISubscriber*> subscribers;
	public:
		Client(std::string _IP, unsigned short authPort);

		void connectTo(std::string IP, unsigned short port) override;
		void disconnect() override;

		void auth(std::string login) override;

		void send(message::IMessage&) override;

		void startRecieving() override;
		void stopRecieving() override;

		void subscribe(message::ISubscriber&) override;
		void unsubscribe(message::ISubscriber&) override;
		void notify_all(message::IMessage&) override;
	};
}

#endif // !CLIENT_H_