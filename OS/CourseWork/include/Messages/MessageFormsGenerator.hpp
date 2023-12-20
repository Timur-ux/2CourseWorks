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

namespace game {
    enum class Action {
        selectWord,
        guessWord
    };

    class GameActionForm : public IForm {
    private:
        Action action;
    public:
        GameActionForm(Action _action) : action(_action) {}

        virtual pt::ptree getForm() override;
    };

    namespace request {
        class Form : public GameActionForm {
        public:
            Form(Action action) : GameActionForm(action) {}
        };
    } // ! request

    namespace reply {
        class Form : public GameActionForm {
        private:
            long long id;
            std::string login;
        public:
            Form(Action action, long long _id, std::string _login) : GameActionForm(action), id(_id), login(_login) {}

            virtual pt::ptree getForm() override;
        };

        class SelectWordForm : public Form {
        private:
            std::string word;
        public:
            SelectWordForm(std::string _word, long long id, std::string login) 
                : Form(Action::selectWord, id, login)
                , word(_word) {}
            
            pt::ptree getForm() override;
        };

        class GuessWordForm : public Form {
        private:
            std::string word;
            std::string opponent;
        public:
            GuessWordForm(std::string _word, std::string _opponent, long long id, std::string login) 
                : Form(Action::guessWord, id, login)
                , word(_word)
                , opponent(_opponent) {}

            pt::ptree getForm() override;
        };
    } // ! reply
} // ! game




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
