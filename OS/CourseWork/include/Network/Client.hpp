#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include <stdexcept>
#include <vector>
#include <zmq.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "MessageFormsGenerator.hpp"
#include "MessageManager.hpp"
#include "safeBool.hpp"

namespace pt = boost::property_tree;

enum class ClientPorts {
    auth = 0,
    send = 1,
    recv = 2
};

class Client {
private:
    long long id;

    std::string servIP;
    std::vector<unsigned short> ports(3);

    SafeBool isNowRecieving{ false };

    zmq::context_t context;
    zmq::socket_t clientSocketAuth;
    zmq::socket_t clientSocketRecv;
    zmq::socket_t clientSocketSend;
    IMessageManager& messageManager;
public:
    Client(std::string _servIP, unsigned short _authPort, IMessageManager & _messageManager);

    void sendData(pt::ptree data);
    boost::optional<pt::ptree> recieve();
    bool auth(std::string login);

    void startRecieving();
    void stopRecieving();
};

#endif // !CLIENT_H_
