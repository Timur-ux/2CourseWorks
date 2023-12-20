i#ifndef MESSAGE_FORMS_GENERATOR_H_
#define MESSAGE_FORMS_GENERATOR_H_

#include <boost/property_tree/ptree.hpp>
#include <map>

namespace pt = boost::property_tree;

class IForm {
public:
    virtual pt::ptree getForm() = 0;
};

class ServerAuthSucceed : public IForm {
private:
    long long id;
    unsigned short portToSend;
    unsigned short portToRecv;
public:
    ServerAuthSucceed(long long _givenId, unsigned short _portToSend, unsigned short _portToRecv)
        : id(_givenId)
        , portToSend(_portToSend)
        , portToRecv(_portToRecv) {};
    
    pt::ptree getForm() override;
};

class ServerAuthFailed : public IForm {
private:
    std::string message;
public:
    ServerAuthFailed(std::string _message) : message(_message) {}

    pt::ptree getForm() override;
};

class ServerPing : public IForm {
private:
    long long id;
public:
    ServerPing(long long clientId) : id(clientId) {}

    pt::ptree getForm() override;
};

class ClientPing : public IForm {
private:
    long long id;
public:
    ClientPing(long long clientId) : id(clientId) {}

    pt::ptree getForm() override;
};

class MessageForAll : public IForm {
private:
    std::string message;
public:
    MessageForAll(std::string _message) : message(_message) {}

    void setMessage(std::string _message);
    pt::ptree getForm() override;
};

class ClientAuth : public IForm {
private:
    std::string login;
public:
    ClientAuth(std::string _login) : login(_login) {}

    pt::ptree getForm() override;
};

enum class GameAction {
    selectWord,
    guessWord
};

class GameActionRequest : public IForm {
private:
    GameAction action;
public:
    GameActionRequest(GameAction _action) : action(_action){}

    void setAction(GameAction _action);

    pt::ptree getForm() override;
};

class GameActionReply : public IForm {
private:
    long long id;
    std::string login;

    GameAction action;
public:
    GameActionReply(long long _id, std::string _login, GameAction _action) : id(_id), login(_login), action(_action) {}
    
    void setAction(GameAction _action);
    void setGuessed(std::string guessedLogin);
    void setWord(std::string _word);

    pt::ptree getForm() override;
};

#endif // !MESSAGE_FORMS_GENERATOR_H_
