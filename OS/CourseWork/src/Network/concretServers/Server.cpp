#include "Network/concretServers/Server.hpp"
#include "Messages/messageFabric/MessageFabric.hpp"
#include "print.hpp"
#include <sstream>

#define in(container, item) (std::find(std::begin(container), std::end(container), item) != std::end(container))

using namespace network;

static zmq::context_t _context{1};

network::Server::Server(std::string servIP, PortsTriplet freePorts) : context(_context) {

	std::ostringstream oss;
	oss << "tcp://" << servIP << ':';

	ports[ports::auth] = freePorts.port1;
	ports[ports::send] = freePorts.port2;
	ports[ports::recv] = freePorts.port3;

	sockets[ports::auth] = zmq::socket_t(context, ZMQ_REP);
	sockets[ports::send] = zmq::socket_t(context, ZMQ_PUB);
	sockets[ports::recv] = zmq::socket_t(context, ZMQ_PULL);

	sockets[ports::auth].bind((oss.str() + std::to_string(ports[ports::auth])).c_str());
	sockets[ports::send].bind((oss.str() + std::to_string(ports[ports::send])).c_str());
	sockets[ports::recv].bind((oss.str() + std::to_string(ports[ports::recv])).c_str());
}

void network::Server::startAuth()
{
	isNowAuth = true;
	while (isNowAuth) {
		zmq::message_t message;
		sockets[ports::auth].recv(message);

		std::istringstream iss(
			std::string(static_cast<char*>(message.data()), message.size())
		);

		pt::ptree data;
		pt::read_json(iss, data);

		auto authMessage = message::fabric::MessageFabric::getInstance()
			.getFromRawData(data);

		if (!authMessage.has_value()) {
			printErr() << "Error: bad auth message" << std::endl;
			continue;
		}

		authMessage.value()->accept(*this);
		notify_all(authMessage.value());
	}
}

void network::Server::visit(message::request::IAuth& message) {
	std::string login = message.getLogin();
	
	bool found = false;
	for (auto& client : clients) {
		if (client.second.login == login) {
			found = true;
			break;
		}
	}

	std::shared_ptr<message::IMessage> data;
	if (found) {
		data = message::fabric::MessageFabric::getInstance()
			.getReply(
				message::fabric::reply::Auth(false, "", 0, 0, 0, "", 0)
			);
	}
	else {
		data = message::fabric::MessageFabric::getInstance()
			.getReply(
				message::fabric::reply::Auth(true, serverIP, ports[ports::recv], ports[ports::send], freeId++, login, overallFilter)
			);
	}

	std::ostringstream oss;
	pt::write_json(oss, data->getData());

	zmq::message_t reply(oss.str());
	sockets[ports::auth].send(reply, zmq::send_flags::none);
}

void network::Server::stopAuth()
{
	isNowAuth = false;
}

void network::Server::sendForAll(message::IMessage& message)
{
	auto data = message.getData();
	std::ostringstream oss;

	oss << overallFilter << ' ';
	pt::write_json(oss, data);

	zmq::message_t sendMessage(oss.str());
	sockets[ports::send].send(sendMessage, zmq::send_flags::none);
}

void network::Server::sendFor(long long id, message::IMessage& message)
{
	auto data = message.getData();
	std::ostringstream oss;

	oss << id << ' ';
	pt::write_json(oss, data);

	zmq::message_t sendMessage(oss.str());
	sockets[ports::send].send(sendMessage, zmq::send_flags::none);
}

void network::Server::startRecieving()
{
	isNowRecv = true;
	while (isNowRecv) {
		zmq::message_t recv;
		sockets[ports::recv].recv(recv);

		std::istringstream iss(
			std::string(static_cast<char*>(recv.data()), recv.size())
		);
		pt::ptree data;
		pt::read_json(iss, data);

		auto message = message::fabric::MessageFabric::getInstance()
			.getFromRawData(data);
		
		if (!message.has_value()) {
			printErr() << "Warning: recieved message not recognized" << std::endl;
			continue;
		}

		message.value()->accept(*this);

		notify_all(message.value());
	}
}

void network::Server::stopRecieving()
{
	isNowRecv = false;
}

std::list<long long> network::Server::ping(std::list<long long> idToPing)
{
	pingList.erase(std::begin(pingList), std::end(pingList));

	std::shared_ptr<message::IMessage> pingMessage = message::fabric::MessageFabric::getInstance()
		.getRequest(
			message::fabric::request::Ping()
		);

	for (auto id : idToPing) {
		sendFor(id, *pingMessage);
	}

	std::this_thread::sleep_for(1s);
	
	std::list<long long> result;

	for (auto id : idToPing) {
		if (!in(pingList, id)) {
			result.push_back(id);
		}
	}
	
	return result;
}

void network::Server::visit(message::reply::IPing& message)
{
	pingList.push_back(message.getId());
}

void network::Server::subscribe(message::ISubscriber& subscriber)
{
	subscribers.push_back(&subscriber);
}

void network::Server::unsubscribe(message::ISubscriber& subscriber)
{
	auto subscriberIt = std::find(std::begin(subscribers), std::end(subscribers), &subscriber);
	if (subscriberIt == std::end(subscribers)) {
		return;
	}

	subscribers.erase(subscriberIt);
}

void network::Server::notify_all(std::shared_ptr<message::IMessage> message)
{
	for (auto subs : subscribers) {
		subs->notify(message);
	}
}

boost::optional<long long> network::Server::getIdByLogin(std::string login)
{
	for (auto& client : clients) {
		if (client.second.login == login) {
			return client.first;
		}
	}

	return boost::none;
}