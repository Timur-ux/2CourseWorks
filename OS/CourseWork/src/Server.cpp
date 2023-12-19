#include "Server.hpp"
#include <sstream>
#include <algorithm>
#include <iostream>

#define all(x) std::begin(x), std::end(x)
#define in(container, item) std::find(all(container), item) != std::end(container)

pt::ptree Server::checkAndSetNewUser(pt::ptree authData)
{
    boost::optional<std::string> login = authData.get_optional<std::string>("Auth.login");

    if (login) {
        if (clients.find(login) == std::end(clients)) {
            long long id = freeId++;
            clients[login] = id;
            IForm former = ServerAuthSucceed(id, ports[ServerPorts::recv], ports[ServerPorts::send]);
            authData = former.getForm();
        }
        else {
            IForm former = ServerAuthFailed("Login already exist");
            authData = former.getForm();
        }
    }
    else {
        IForm former = ServerAuthFailed("Invalid authentication data: Auth.login field don't found");
        authData = former.getForm();
    }

    return authData;
}

Server::Server(std::string _IP, std::vector<unsigned short> _ports, IMessageManager & _messageManager)
    : IP(_IP)
    , ports(_ports)
    , messageManager(_messageManager)
    , context(1)
    , servSocketSend(context, ZMQ_PUB)
    , servSocketRecv(context, ZMQ_PULL)
    , servSocketAuth(context, ZMQ_REP) {
    
    size_t portsSize = _ports.size();
    if (portsSize != 3) {
        throw std::invalid_argument("Server must get 3 free ports. " + std::to_string(portsSize) + "given");
    }
    
    std::stringstream addrStream;
    addrStream << "tcp://" << IP << ':';

    servSocketAuth.bind((addrStream.str() + std::to_string(ports[ServerPorts::auth])).c_str());
    servSocketSend.bind((addrStream.str() + std::to_string(ports[ServerPorts::send])).c_str());
    servSocketRecv.bind((addrStream.str() + std::to_string(ports[ServerPorts::recv])).c_str());

    std::thread(&Server::startRecieving, this).detach();
    std::thread(&Server::startAuth, this).detach();
}

void Server::startAuth()
{
    isNowAuth = true;

    while (isNowAuth) {
        zmq::message_t request;

        servSocketAuth.recv(request, zmq::recv_flags::none);

        std::istringstream iss(std::string(request.data(), request.size()));

        pt::ptree data;
        pt::read_json(iss, data);

        pt::ptree result = checkAndSetNewUser(data);

        std::ostringstream oss;
        pt::write_json(oss, result);

        zmq::message_t response(oss.str());

        servSocketAuth.send(response, zmq::send_flags::none);
    }
}

void Server::stopAuth()
{
    isNowAuth = false;
}

void Server::sendTo(long long id, pt::ptree data) {
    data.put<unsigned short>("Message.sender", ports[ServerPorts::send]);
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

boost::optional<Message> Server::getMessage()
{
    if (dataMQ.empty()) {
        return boost::none;
    }

    Message result = dataMQ.front();
    dataMQ.pop();

    return result;
}

Socket Server::getAuthSocket()
{
    return Socket(IP, ports[ServerPorts::auth]);
}

std::list<long long> Server::ping(std::list<long long> ids)
{
    for (long long& id : ids) {
        IForm former = ServerPing(id);
        sendTo(id, former.getForm());
    }

    std::this_thread::sleep_for(300ms);

    for (int i = 0; i < pingMQ.size(); ++i) {
        Message message = pingMQ.front();
        pingMQ.pop();
        long long id = message.data.get<long long>("Message.sender");
        
        if (in(ids, id)) {
            ids.erase(std::find(std::begin(ids), std::end(ids), id));
        }
    }

    return ids;
}

void Server::startRecieving() {
    isNowRecieving = true;
    while (isNowRecieving) {
        zmq::message_t message;

        servSocketRecv.recv(message, zmq::recv_flags::none);

        std::string strMessage(static_cast<char*>(message.data()), message.size());
        std::istringstream iss(strMessage);
        pt::ptree data;

        pt::read_json(iss, data);

        messageManager.push(data);
    }
}

void Server::stopRecieving() {
    isNowRecieving = false;
}

boost::optional<long long> Server::getIdByLogin(std::string login)
{
    auto clientIt = clients.find(login);
    if (clientIt == std::end(clients)) {
        return boost::none;
    }

    return clientIt->second;
}
