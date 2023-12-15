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
    std::thread(&Server::startPrintingMessages, this).detach();
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

std::list<long long> Server::pingall() {
    for (long long & id : clients) {
        pt::ptree data;
        data.put<std::string>("Request.type", calc_center_command::ping);
        data.put<long long>("Request.id", id);

        sendTo(id, data);
    }
    std::this_thread::sleep_for(300ms);

    if (pingMQ.size() == clients.size()) {
        while (!pingMQ.empty()) {
            pingMQ.pop();
        }

        return {};
    }

    std::list<long long> goodId;
    while (!pingMQ.empty()) {
        Message current = pingMQ.front();
        pingMQ.pop();

        goodId.push_back(current.senderId);
    }

    std::list<long long> badId;
    for (long long & id : clients) {
        if (in(goodId, id)) {
            continue;
        }

        badId.push_back(id);
    }

    return badId;
}

void Server::startRecieving() {
    isNowRecieving = true;
    while (isNowRecieving) {
        zmq::message_t message;

        servSocketRecv.recv(message, zmq::recv_flags::none);

        std::string strMessage(reinterpret_cast<char*>(message.data()), message.size());
       
        std::istringstream iss(strMessage);
        long long id;
        pt::ptree data;
        MessageType type;

        iss >> id;
        pt::read_json(iss, data);

        if (data.get<std::string>("Response.type") == calc_center_command::ping) {
            type = MessageType::ping;
            pingMQ.push(Message( id, type, data ));
        }
        else if(data.get<std::string>("Response.type") == calc_center_command::exec) {
            type = MessageType::data;
            dataMQ.push(Message( id, type, data ));
        }
    }
}

void Server::stopRecieving() {
    isNowRecieving = false;
}

void Server::startPrintingMessages() {
    isNowPrinting = true;

    while (isNowPrinting) {
        while (!dataMQ.empty()) {
            Message current = dataMQ.front();
            dataMQ.pop();

            long long id = current.senderId;
            pt::ptree data = current.data;

            std::ostringstream oss;

            oss << data.get<std::string>("Response.status") << " : " << id;
            
            std::string responseType = data.get<std::string>("Response.execType");

            if (responseType == "GetValue") {
                oss << " : ";

                bool found = data.get<bool>("Response.found");
                if (found) {
                    int value = data.get<int>("Response.value");
                    oss << value;
                }
                else {
                    oss << "Not Found";
                }
            }
            oss << std::endl;

            print() << oss.str();
        }
    }
}

void Server::stopPrintingMessages() {
    isNowPrinting = false;
}
