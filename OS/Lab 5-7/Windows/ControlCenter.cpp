#include <iostream>
#include <memory>
#include <thread>
#include <string>
#include <WinSock2.h>
#include <Windows.h>
#include <sstream>

#include "Server.hpp"

const std::string caclucatingCenterName = "CalculatingCenter.exe";

auto main(int argc, char * argw[]) -> int {
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

    std::thread(&Server::startListen, server).detach();

    std::string command;
    while (true) {
        std::cin >> command;
        if (command == "create") {
            int id, parent;
            std::cin >> id >> parent;

            STARTUPINFO si;
            PROCESS_INFORMATION pi;
            ZeroMemory(&si, sizeof(si));
            ZeroMemory(&pi, sizeof(pi));

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
                , &pi
            )) {
                std::cout << "OK: " << pi.dwProcessId << std::endl;
            }
        }
    }
}