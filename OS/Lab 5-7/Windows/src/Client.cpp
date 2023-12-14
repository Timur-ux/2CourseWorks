#include "Client.hpp"

#include <sstream>
#include <iostream>

Client::Client(std::string _servIP, unsigned short _portToRecv, unsigned short _portToSend, long long _id)
    : servIP(_servIP)
    , portToRecv(_portToRecv)
    , portToSend(_portToSend)
    , id(_id)
    , context(1)
    , clientSocketRecv(context, ZMQ_SUB)
    , clientSocketSend(context, ZMQ_PUSH) {

    std::ostringstream oss;
    oss << "tcp://" << servIP << ':';
    clientSocketRecv.connect((oss.str() + std::to_string(portToRecv)).c_str());
    clientSocketSend.connect((oss.str() + std::to_string(portToSend)).c_str());

    clientSocketRecv.setsockopt(ZMQ_SUBSCRIBE, &id, sizeof(id));
}

void Client::sendData(pt::ptree data) {
    std::ostringstream oss;

    data.put<long long>("Response.id", id);

    oss << id << ' ';
    pt::write_json(oss, data);

    zmq::message_t message(oss.str());

    clientSocketSend.send(message, zmq::send_flags::none);
}

pt::ptree Client::recieve() {
    zmq::message_t message;

    clientSocketRecv.recv(message, zmq::recv_flags::none);

    std::istringstream iss(reinterpret_cast<char *>(message.data()));
    long long id;
    pt::ptree result;

    iss >> id;

    pt::read_json(iss, result);
    return result;
}
