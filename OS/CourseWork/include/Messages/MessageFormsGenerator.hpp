i#ifndef MESSAGE_FORMS_GENERATOR_H_
#define MESSAGE_FORMS_GENERATOR_H_

#include <boost/property_tree/ptree.hpp>
#include <map>
#include <list>

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
        guessWord,
        endGame
    };

    enum class RequestToServer {
        createNewGame,
        getLoginsList
    };

    class GameActionForm : public IForm {
    private:
        Action action;
    public:
        GameActionForm(Action _action) : action(_action) {}

        virtual pt::ptree getForm() override;
    };

    namespace request {
        class RequestToServerForm : public IForm {
        private:
            RequestToServer type;
            std::string senderLogin;
        public:
            RequestToServerForm(RequestToServer _type, std::string _senderLogin) 
                : type(_type)
                , senderLogin(_senderLogin) {}

            virtual pt::ptree getForm() override;
        };

        class GetLoginsListForm : public RequestToServerForm {
        public:
            GetLoginsListForm(std::string senderLogin)
                : RequestToServerForm(RequestToServer::getLoginsList, senderLogin) {}

            pt::ptree getForm() final;
        };

        class CreateNewGameForm : public RequestToServerForm {
        private:
            std::list<std::string> logins;
        public:
            CreateNewGameForm(std::string senderLogin, std::list<std::string> logins)
                : RequestToServerForm(RequestToServer::createNewGame, senderLogin) {}

            pt::ptree getForm() final;
        };

        class Form : public GameActionForm {
        public:
            Form(Action action) : GameActionForm(action) {}
        };

        class CreateNewGameForm : public IForm {
        private:
            std::list<std::string> logins;
        public:
            CreateNewGameForm(std::list<std::string> _logins) : logins(_logins) {}

            pt::ptree getForm() override;
        };
    } // ! request

    namespace reply {
        class ReplyFromServerForm : public IForm {
        private:
            game::RequestToServer type;
        public:
            ReplyFromServerForm(game::RequestToServer _type) : type(_type) {}

            virtual pt::ptree getForm() override;
        };

        class GetLoginsListForm : public ReplyFromServerForm {
        private:
            std::list <std::string> logins;
        public:
            GetLoginsListForm(std::list<std::string> _logins) : logins(_logins) {}

            pt::ptree getForm() final;
        };

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

#endif // !MESSAGE_FORMS_GENERATOR_H_
