#ifndef SERVER_H_
#define SERVER_H_

#include <map>
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
#include <boost/optional.hpp>

#include "print.hpp"
#include "safeBool.hpp"
#include "MessageQueue.hpp"
#include "MessageFormsGenerator.hpp"
#include "Socket.hpp"
#include "MessageManager.hpp"

using namespace std::chrono_literals;
namespace pt = boost::property_tree;

enum class ServerPorts {
    auth = 0,
    send = 1,
    recv = 2
};

struct Message {
    pt::ptree data;

    Message(pt::ptree _data) : data(_data) {}
};

class Server {
private:
    std::string IP;
    std::vector<unsigned short> ports;

    zmq::context_t context;
    zmq::socket_t servSocketAuth;
    zmq::socket_t servSocketSend;
    zmq::socket_t servSocketRecv;

    std::map<std::string, long long> clients;

    SafeBool isNowRecieving{ false };
    SafeBool isNowAuth{ false };
    
    IMessageManager& messageManager;
    long long freeId = 1;
    pt::ptree checkAndSetNewUser(pt::ptree authData);
public:
    Server(std::string IP, std::vector<unsigned short> _ports, IMessageManager & _messageManager);

    void startRecieving();
    void stopRecieving();

    void startAuth();
    void stopAuth();

    void sendTo(long long id, pt::ptree data);

    void addClient(long long id);
    void removeClient(long long id);

    Socket getAuthSocket();

    std::list<long long> ping(std::list<long long> ids);

    boost::optional<long long> getIdByLogin(std::string login);

};

#endif // !SERVER_H_
