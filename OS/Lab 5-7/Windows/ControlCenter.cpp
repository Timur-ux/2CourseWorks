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

void printLastDataFromStream(std::stringstream& os);

auto main(int argc, char * argw[]) -> int {
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
    topology.subscribe(server.get());
    std::thread(&Server::startListen, server).detach();
    std::thread(&Server::startRecieving, server).detach();
    std::cerr << "Server: start listening" << std::endl;

    while (true) {
        std::string request;
        std::string command;
        std::getline(std::cin, request);
        
        if (request.size() < 2) {
            continue;
        }

        std::stringstream requestStream(request);
        requestStream >> command;

        if (command == "create") {
            long long id;
            requestStream >> id;


            STARTUPINFO si;
            PROCESS_INFORMATION* pi = new PROCESS_INFORMATION;
            ZeroMemory(&si, sizeof(si));
            ZeroMemory(pi, sizeof(*pi));
            try {
                topology.add(id, { 0, pi });
            }
            catch (std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                continue;
            }

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
            requestStream >> id;
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
            try {
                server->sendTo(socket, strToVChar(calc_center_command::terminate));
            }
            catch (std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
            
            server->disconnectClient(socket);
        }
        else if (command == "exec") {
            std::string name;
            long long id, value;

            std::string command;
            
            std::stringstream sendStream;
            
            requestStream >> id >> name;
            sendStream << calc_center_command::exec << ' ' << name;
            if (requestStream >> value) {
                sendStream << ' ' << value;
            }

            SOCKET socket;
            try {
                socket = topology.find(id).socket;
            }
            catch (std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                continue;
            }

            try {
                server->sendTo(socket, strToVChar(sendStream.str()));
            }
            catch (std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                topology.remove(id);
            }
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