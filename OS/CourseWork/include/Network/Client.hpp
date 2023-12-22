#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include <stdexcept>
#include <vector>
#include <map>
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
    long long id = 0;
    std::string login;

    std::string servIP;
    std::map<ClientPorts, unsigned short> ports;

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
    
    void connectTo(std::string _servIP, unsigned short _authPort);
    void disconnect();

    void startRecieving();
    void stopRecieving();

    long long getId() {
        return id;
    }

    std::string getLogin() {
        return login;
    }
};

#endif // !CLIENT_H_
