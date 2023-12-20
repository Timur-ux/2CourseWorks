#include "Network/Client.hpp"
#include "print.hpp"

#include <sstream>
#include <iostream>

Client::Client(std::string _servIP, unsigned short _authPort, IMessageManager & _messageManager)
    : servIP(_servIP)
    , messageManager(_messageManager)
    , context(1)
    , clientSocketRecv(context, ZMQ_SUB)
    , clientSocketSend(context, ZMQ_PUSH)
    , clientSocketAuth(context, ZMQ_REQ) {
    std::ostringstream oss;
    oss << "tcp://" << servIP << ':';
    
    ports[ClientPorts::auth] = _authPort;

    clientSocketAuth.connect((oss.str() + std::to_string(ports[ClientPorts::auth])).c_str());
}

void Client::sendData(pt::ptree data) {
    std::ostringstream oss;

    data.put<long long>("Client.id", id);

    oss << id << ' ';
    pt::write_json(oss, data);

    zmq::message_t message(oss.str());

    clientSocketSend.send(message, zmq::send_flags::none);
}

pt::ptree Client::recieve() {
    if (isNowRecieving) {
        printErr() << "Continious recieving is enable now."
             << "Call client.stopRecieving() to stop it, and then call client.recieve()" << std::endl;
        return boost::none;
    }

    zmq::message_t message;

    clientSocketRecv.recv(message, zmq::recv_flags::none);

    std::string messageData(static_cast<char*>(message.data()), message.size());
    std::istringstream iss(messageData);
    long long id;
    pt::ptree result;

    iss >> id;
    pt::read_json(iss, result);

    return result;
}

bool Client::auth(std::string login)
{
    IForm former = ClientAuth(login);
    pt::ptree sendData = former.getForm();

    std::ostringstream oss;
    pt::write_json(oss, sendData);
    zmq::message_t request(oss.str());

    clientSocketAuth.send(request, zmq::send_flags::none);

    zmq::message_t response;
    clientSocketAuth.recv(response);

    std::istringstream iss(std::string(static_cast<char*>(message.data()), message.size()));

    pt::ptree recvData;
    pt::read_json(iss, recvData);

    boost::optional<bool> status = recvData.get_optional<std::string>("Auth.status");

    if (status.has_value()) {
        if (status.value()) {
            id = recvData.get<long long>("Auth.givenId");
            ports[ClientPorts::send] = recvData.get<unsigned short>("Auth.portToSend");
            ports[ClientPorts::recv] = recvData.get<unsigned short>("Auth.portToRecv");

            std::ostringstream oss;
            oss << "tcp://" << servIP << ':';

            clientSocketRecv.connect((oss.str() + std::to_string(ports[ClientPorts::recv])).c_str());
            clientSocketSend.connect((oss.str() + std::to_string(ports[ClientPorts::send])).c_str());

            return true;
        }
        else {
            printErr() << "Authentication failed: " << recvData.get<std::string>("Auth.errorMessage") << std::endl;
            return false;
        }
    }
    else {
        printErr() << "Authentication failed: field Auth.status don't found" << std::endl;
        return false;
    }

    return false;
}

void Client::startRecieving()
{
    isNowRecieving = true;

    while (isNowRecieving) {
        zmq::message_t message;

        clientSocketRecv.recv(message);

        messageManager.push(message);
    }
}
