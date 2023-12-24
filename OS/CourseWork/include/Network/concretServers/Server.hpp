#ifndef MAIN_SERVER_H_
#define MAIN_SERVER_H_

#include "../interfaces/IServer.hpp"
#include "../ports.hpp"
#include "safeBool.hpp"

#include <string>
#include <list>
#include <algorithm>
#include <map>
#include <thread>
#include <zmq.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace network {
	struct ClientData {
		long long id;
		std::string login;
	};

	class Server 
		: public IServer
		, public message::request::IMessageVisitor
		, public message::reply::IMessageVisitor {
	private:
		std::map<ports, zmq::socket_t> sockets;
		std::map<long long, ClientData> clients;
		
		SafeBool isNowAuth{ false };
		SafeBool isNowRecv{ false };

		std::list<message::ISubscriber*> subscribers;
		
		zmq::context_t context;
		std::map<ports, zmq::socket_t> sockets;
		std::map<ports, unsigned short> ports;
		std::string serverIP;
		long long freeId = 1;
		long long overallFilter = 0;
	public:
		Server(std::string servIP, PortsTriplet freePorts);

		void startAuth() override;
		void stopAuth() override;
		void visit(message::request::IAuth&) override;

		void sendForAll(message::IMessage&) override;
		void sendFor(long long, message::IMessage&) override;

		void startRecieving() override;
		void stopRecieving() override;

		std::list<long long> ping(std::list<long long>) override;
		void visit(message::reply::IPing&) override;

		void subscribe(message::ISubscriber&) override;
		void unsubscribe(message::ISubscriber&) override;
		void notify_all(message::IMessage&) override;
	};

} // !network

#endif // !MAIN_SERVER_H_