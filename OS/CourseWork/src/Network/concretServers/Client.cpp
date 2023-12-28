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

	if (!sockets[ports::auth]) {
		printErr() << "Error: not connected, please connect to server first" << std::endl;
		return;
	}

	pt::ptree data = message->getData();
	std::ostringstream oss;

	pt::write_json(oss, data);

	zmq::message_t messageToSend(oss.str());
	sockets[ports::auth].send(messageToSend, zmq::send_flags::none);

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
}

void network::Client::visit(message::reply::IAuth& message)
{
	bool status = message.getAuthStatus();
	if (!status) {
		print() << "[Client] Error: Auth failed, please retry" << std::endl;
		std::shared_ptr<message::IMessage> copyMessage = message::fabric::MessageFabric::getInstance()
			.getFromRawData(message.getData()).value();
		notify_all(copyMessage);
		return;
	}

	IP = message.getServerIP();
	login = message.getLogin();
	id = message.getGivenId();
	overallFilter = message.getOverallFilter();

	ports[ports::send] = message.getSendPort();
	ports[ports::recv] = message.getRecvPort();

	std::ostringstream oss;
	oss << "tcp://" << IP << ':';
	sockets[ports::send] = zmq::socket_t(context, ZMQ_PUSH);
	sockets[ports::recv] = zmq::socket_t(context, ZMQ_SUB);

	sockets[ports::send].connect((oss.str() + std::to_string(ports[ports::send]).c_str()));
	sockets[ports::recv].connect((oss.str() + std::to_string(ports[ports::recv]).c_str()));

	std::cout << id << ' ' << overallFilter << std::endl;
	sockets[ports::recv].set(zmq::sockopt::subscribe, std::to_string(id));
	sockets[ports::recv].set(zmq::sockopt::subscribe, std::to_string(overallFilter));

	print() << "Authorized" << std::endl;
	authorized = true;

	std::shared_ptr<message::IMessage> copyMessage = message::fabric::MessageFabric::getInstance()
		.getFromRawData(message.getData()).value();
	notify_all(copyMessage);
}

void network::Client::send(message::IMessage& message)
{
	if (!authorized) {
		print() << "[Client] Error: not authorized";
	}
	std::ostringstream oss;
	pt::ptree data = message.getData();
	
	pt::write_json(oss, data);

	zmq::message_t messageToSend(oss.str());
	sockets[ports::send].send(messageToSend, zmq::send_flags::none);
}

void network::Client::startRecieving()
{
	isNowRecieving = true;
	while (isNowRecieving && authorized) {
		zmq::message_t recv;
		sockets[ports::recv].recv(recv);

		std::istringstream iss(std::string(static_cast<char*>(recv.data()), recv.size()));
		pt::ptree data;

		long long id;
		iss >> id;
		pt::read_json(iss, data);
		print() << "Resieved: " << iss.str() << std::endl;

		boost::optional <std::shared_ptr< message::IMessage >> message = message::fabric::MessageFabric::getInstance()
			.getFromRawData(data);

		if (!message.has_value()) {
			printErr() << "[Client] Error: " << "undefined recieved data" << std::endl;
			continue;
		}

		message.value()->accept(*this);
		notify_all(message.value());
	}
}

void network::Client::stopRecieving()
{
	isNowRecieving = false;
}

void network::Client::subscribe(message::ISubscriber& sub)
{
	subscribers.push_back(&sub);
}

void network::Client::unsubscribe(message::ISubscriber& sub)
{
	auto subIt = std::find(std::begin(subscribers), std::end(subscribers), &sub);
	if (subIt == std::end(subscribers)) {
		return;
	}

	subscribers.erase(subIt);
}

void network::Client::notify_all(std::shared_ptr<message::IMessage> message)
{
	for (auto& subscriber : subscribers) {
		subscriber->notify(message);
	}
}
