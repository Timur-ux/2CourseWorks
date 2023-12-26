#include "Network/concretServers/Client.hpp"
#include <sstream>
#include "print.hpp"

using namespace network;

static zmq::context_t _context{1};

network::Client::Client(std::string _IP, unsigned short authPort) : context(_context) {
	IP = _IP;
	ports[ports::auth] = authPort;

	connectTo(IP, ports[ports::auth]);
}

void network::Client::connectTo(std::string IP, unsigned short port)
{
	this->IP = IP;
	ports[ports::auth] = port;

	sockets[ports::auth] = zmq::socket_t(context, ZMQ_REQ);

	std::ostringstream oss;
	oss << "tcp://" << IP << ':' << ports[ports::auth];
	sockets[ports::auth].connect(oss.str().c_str());
}

void network::Client::disconnect()
{
	std::ostringstream oss;
	oss << "tcp://" << IP << ':';
	for (auto& port : ports) {
		network::ports curPortType = port.first;
		unsigned short curPort = port.second;
		
		sockets[curPortType].disconnect((oss.str() + std::to_string(curPort)).c_str());
	}
}

void network::Client::auth(std::string login)
{
	std::shared_ptr<message::IMessage> message = message::fabric::MessageFabric::getInstance()
		.getRequest(
			message::fabric::request::Auth(login)
		);

	if (!sockets[ports::auth].connected()) {
		printErr() << "Error: not connected, please connect to server first" << std::endl;
		return;
	}

	pt::ptree data = message->getData();
	std::ostringstream oss;

	pt::write_json(oss, data);

	zmq::message_t messageToSend(oss.str());
	sockets[ports::auth].send(messageToSend);

	zmq::message_t recievedMessage;
	sockets[ports::auth].recv(recievedMessage);

	std::istringstream iss(std::string(static_cast<char*>(recievedMessage.data()), recievedMessage.size()));

	pt::ptree recvData;
	pt::read_json(iss, recvData);

	boost::optional<std::shared_ptr<message::IMessage>> recvMessage = message::fabric::MessageFabric::getInstance()
		.getFromRawData(recvData);

	if (!recvMessage.has_value()) {
		printErr() << "[Client] Error: Undefined message" << std::endl;
	}

	recvMessage.value()->accept(*this);
	notify_all(*recvMessage.value());
}

void network::Client::visit(message::reply::IAuth& message)
{
	bool status = message.getAuthStatus();
	if (!status) {
		printErr() << "[Client] Error: Auth failed, please retry" << std::endl;
	}

	login = message.getGivenId();
	id = message.getGivenId();
	overallFilter = message.getOverallFilter();

	ports[ports::send] = message.getSendPort();
	ports[ports::recv] = message.getRecvPort();

	std::ostringstream oss;
	oss << "tcp://" << IP << ':';

	sockets[ports::send] = zmq::socket_t(context, ZMQ_PULL);
	sockets[ports::recv] = zmq::socket_t(context, ZMQ_PUB);

	sockets[ports::send].connect((oss.str() + std::to_string(ports[ports::send]).c_str()));
	sockets[ports::recv].connect((oss.str() + std::to_string(ports[ports::recv]).c_str()));
}

