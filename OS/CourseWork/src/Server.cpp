#include "Server.hpp"
#include <sstream>
#include <algorithm>
#include <iostream>

#define all(x) std::begin(x), std::end(x)
#define in(container, item) std::find(all(container), item) != std::end(container)

Server::Server(std::string _IP, unsigned short _port1, unsigned short _port2)
    : IP(_IP)
    , port1(_port1)
    , port2(_port2)
    , context(1)
    , servSocketSend(context, ZMQ_PUB)
    , servSocketRecv(context, ZMQ_PULL) {
    std::stringstream addrStream;
    addrStream << "tcp://" << IP << ':';

    servSocketSend.bind((addrStream.str() + std::to_string(port1)).c_str());
    servSocketRecv.bind((addrStream.str() + std::to_string(port2)).c_str());

    std::thread(&Server::startRecieving, this).detach();
}

void Server::sendTo(long long id, pt::ptree data) {
    std::stringstream messageStream;

    messageStream << id << ' ';
    pt::write_json(messageStream, data);

    zmq::message_t message(messageStream.str());
    servSocketSend.send(message, zmq::send_flags::none);
}

void Server::addClient(long long id) {
    clients.push_back(id);
}

void Server::removeClient(long long id) {
    auto clientIt = std::find(all(clients), id);

    if (clientIt == std::end(clients)) {
        return;
    }

    clients.erase(clientIt);
}

bool Server::isThereMessages()
{
    return !dataMQ.empty();
}

Message Server::getMessage()
{
    if (dataMQ.empty()) {
        throw std::runtime_error("There are no free messages");
    }

    Message result = dataMQ.front();
    dataMQ.pop();

    return result;
}

void Server::startRecieving() {
    isNowRecieving = true;
    while (isNowRecieving) {
        zmq::message_t message;

        servSocketRecv.recv(message, zmq::recv_flags::none);

        std::string strMessage(reinterpret_cast<char*>(message.data()), message.size());
        std::istringstream iss(strMessage);
        pt::ptree data;

        pt::read_json(iss, data);

        dataMQ.push(Message( id, data ));
    }
}

void Server::stopRecieving() {
    isNowRecieving = false;
}

