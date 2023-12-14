#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include <stdexcept>
#include <vector>
#include <zmq.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace pt = boost::property_tree;

class Client {
private:
    long long id;

    std::string servIP;
    unsigned short portToRecv;
    unsigned short portToSend;

    zmq::context_t context;
    zmq::socket_t clientSocketRecv;
    zmq::socket_t clientSocketSend;

public:
    Client(std::string _servIP, unsigned short _portToRecv, unsigned short _portToSend, long long _id);

    void sendData(pt::ptree data);
    pt::ptree recieve();
};

#endif // !CLIENT_H_
