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

class Server {
protected:
    std::string IP;
    std::map<ServerPorts, unsigned short> ports;

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
    pt::ptree provideAuthAndGetResult();
public:
    Server(std::string IP, std::vector<unsigned short> _ports, IMessageManager & _messageManager);

    void startRecieving();
    void stopRecieving();

    virtual void startAuth();
    void stopAuth();

    void sendTo(long long id, pt::ptree data);
    void sendForAll(pt::ptree data);

    Socket getAuthSocket();

    boost::optional<long long> getIdByLogin(std::string login);

    std::map<std::string, long long> getClients() const;

};

#endif // !SERVER_H_
