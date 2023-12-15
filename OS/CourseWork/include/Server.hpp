#ifndef SERVER_H_
#define SERVER_H_

#include <list>
#include <string>
#include <stdexcept>
#include <shared_mutex>
#include <vector>
#include <zmq.hpp>
#include <thread>
#include <chrono>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "print.hpp"
#include "safeBool.hpp"
#include "MessageQueue.hpp"
#include "CalcCenterCommands.hpp"

using namespace std::chrono_literals;
namespace pt = boost::property_tree;


struct Message {
    long long senderId;
    pt::ptree data;

    Message(long long _senderId, pt::ptree _data)
        : senderId(_senderId)
        , data(_data) {}
};

class Server {
private:
    std::string IP;
    unsigned short port1;
    unsigned short port2;

    zmq::context_t context;
    zmq::socket_t servSocketSend;
    zmq::socket_t servSocketRecv;

    std::list<long long> clients;

    SafeBool isNowRecieving{ false };
    
    MessageQueue<Message> dataMQ;
public:
    Server(std::string IP, unsigned short port1, unsigned short port2);

    void startRecieving();
    void stopRecieving();

    void sendTo(long long id, pt::ptree data);

    void addClient(long long id);
    void removeClient(long long id);

    bool isThereMessages();
    Message getMessage();

};

#endif // !SERVER_H_
