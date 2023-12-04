#include <iostream>
#include <memory>
#include <thread>
#include <string>
#include <WinSock2.h>
#include <Windows.h>
#include <sstream>
#include <vector>

#include "Server.hpp"
#include "BinTree.hpp"
#include "CalcCenterCommands.hpp"

const std::string caclucatingCenterName = "CalculatingCenter.exe";

auto main(int argc, char * argw[]) -> int {
    std::cin.tie(0);

    BinTree topology;

    std::string IP = "127.0.0.1";
    int port = 1234;

    if (argc == 3) {
        IP = argw[1];
        port = atoi(argw[2]);
    }

    std::shared_ptr<Server> server;
    try {
        server = std::make_shared<Server>(IP, port);
    }
    catch (std::exception & e) {
        std::cerr << "Server initialization failed: " << e.what() << std::endl;
        return 1;
    }

    std::cerr << "Server initialization done" << std::endl;

    server->subscribe(&topology);

    std::thread(&Server::startListen, server).detach();
    std::cerr << "Server: start listening" << std::endl;

    std::string command;
    while (true) {
        MessageQueue<Message>& recievedMessages = server->getRecievedMessages();

        while (!recievedMessages.empty()) {
            Message message = recievedMessages.front();
            recievedMessages.pop();

            std::cout << message.data.data() << std::endl;
        }
        
        std::cin >> command;
        if (command == "create") {
            long long id, parent;
            std::cin >> id >> parent;

            STARTUPINFO si;
            PROCESS_INFORMATION* pi = new PROCESS_INFORMATION;
            ZeroMemory(&si, sizeof(si));
            ZeroMemory(pi, sizeof(*pi));

            topology.add(id, { 0, pi });

            std::stringstream commandStream;
            commandStream << caclucatingCenterName << ' ' << IP << ' ' << port;
            if (!CreateProcess(
                NULL
                , (LPSTR)commandStream.str().c_str()
                , NULL
                , NULL
                , FALSE
                , 0
                , NULL
                , NULL
                , &si
                , pi
            )) {
                std::cerr << "Error: CreateProcess failed #" << GetLastError() << std::endl;
            }
            else {
                std::cout << "OK: " << pi->dwProcessId << std::endl;
            }
        }
        else if (command == "kill") {
            long long id;
            std::cin >> id;
            if (id < 0) {
                id *= -1;
            }

            SOCKET socket;
            try {
                socket = topology.find(id).socket;
            }
            catch (std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                continue;
            }

            topology.remove(id);
            server->sendTo(socket, strToVChar(calc_center_command::terminate));
        }
        else if (command == "exec") {
            std::string name;
            long long id, value;

            std::string command;
            
            getline(std::cin, command);
            std::stringstream commandStream(command);
            std::stringstream sendStream;
            
            commandStream >> id >> name;
            if (commandStream >> value) {
                sendStream << calc_center_command::exec << ' ' << name << ' ' << value;
            }
            else {
                sendStream << calc_center_command::exec << ' ' << name;
            }

            SOCKET socket;
            try {
                socket = topology.find(id).socket;
            }
            catch (std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                continue;
            }

            server->sendTo(socket, strToVChar(sendStream.str()));
            std::thread(&Server::recieveFrom, server, socket).detach();
        }
        else if (command == "pingall") {
            std::vector<SOCKET> deadsockets = server->chekAndGetDeadSockets(3, 0);
            std::vector<long long> deadId;
            if (deadsockets.size() == 0) {
                std::cout << "Ok: -1" << std::endl;
                continue;
            }
            for (SOCKET deadsocket : deadsockets) {
                deadId.push_back(topology.findIdWithSock(deadsocket));
            }

            std::cout << "Ok: ";
            for (int i = 0; i < deadId.size(); ++i) {
                std::cout << deadId[i];
                if (i == deadId.size() - 1) {
                    break;
                }
                std::cout << ';';
            }
            std::cout << std::endl;
        } 
        else {
            std::cout << "Undefined command" << std::endl;
            continue;
        }
    }
}