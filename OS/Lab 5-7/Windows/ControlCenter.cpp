#include <iostream>
#include <memory>
#include <thread>
#include <string>
#include <Windows.h>
#include <sstream>
#include <vector>
#include <boost/property_tree/ptree.hpp>

#include "Server.hpp"
#include "BinTree.hpp"
#include "CalcCenterCommands.hpp"

namespace pt = boost::property_tree;

const std::string caclucatingCenterName = "CalculatingCenter.exe";

pt::ptree createExecRequest(std::string name, bool isSet = false, int valToSet = 0);

auto main(int argc, char * argw[]) -> int {
    std::string IP;
    unsigned short port1, port2;

    if (argc != 4) {
        throw std::invalid_argument("Usage ./<progam name> <IP> <free port 1> <free port 2>");
    }

    IP = argw[1];
    port1 = atoi(argw[2]);
    port2 = atoi(argw[3]);

    BinTree topology;
    Server server(IP, port1, port2);

     std::cerr << "Server initialization done" << std::endl;

     while (true) {
         std::string request;
         std::string command;
         std::getline(std::cin, request);

         if (request.size() < 1) {
             continue;
         }

         std::stringstream requestStream(request);
         requestStream >> command;

         if (command == "create") {
             long long id;
             requestStream >> id;


             STARTUPINFO si;
             PROCESS_INFORMATION * pi = new PROCESS_INFORMATION;
             ZeroMemory(&si, sizeof(si));
             ZeroMemory(pi, sizeof(*pi));
             try {
                 topology.add(id, { pi });
                 server.addClient(id);
             }
             catch (std::exception & e) {
                 std::cerr << "Error: " << e.what() << std::endl;
                 continue;
             }

             std::stringstream commandStream;
             commandStream << caclucatingCenterName << ' ' << IP << ' ' << port1 << ' ' << port2 << ' ' << id;
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

             PROCESS_INFORMATION * pi;
             try {
                 pi = topology.find(id).pi;
             }
             catch (std::exception & e) {
                 std::cerr << "Error: " << e.what() << std::endl;
                 continue;
             }

             topology.remove(id);
             pt::ptree data;
             data.put<std::string>("Request.type", calc_center_command::terminate);
             try {
                 server.sendTo(id, data);
                 server.removeClient(id);
             }
             catch (std::exception & e) {
                 std::cerr << "Error: " << e.what() << std::endl;
             }
         }
         else if (command == "exec") {
             std::string name;
             long long id, value = 0;
             bool isSet = false;
             pt::ptree data;

             std::string command;

             requestStream >> id >> name;


             if (requestStream >> value) {
                 isSet = true;
             }

             data = createExecRequest(name, isSet, value);
             try {
                 topology.find(id);
             }
             catch (std::exception & e) {
                 std::cerr << "Error: " << e.what() << std::endl;
                 continue;
             }

             try {
                 server.sendTo(id, data);
             }
             catch (std::exception & e) {
                 std::cerr << "Error: " << e.what() << std::endl;
             }
         }
         else if (command == "pingall") {
             std::list<long long> badId = server.pingall();

             if (badId.empty()) {
                 print() << "OK: -1" << std::endl;
             }
             else {
                 std::ostringstream oss;
                 oss << "OK: ";

                 for (long long & id : badId) {
                     oss << id << ' ';
                 }

                 print() << oss.str();
             }
         }
         else {
             std::cout << "Undefined command" << std::endl;
             continue;
         }
     }
}

pt::ptree createExecRequest(std::string name, bool isSet, int valToSet) {
    pt::ptree data;

    data.put<std::string>("Request.type", calc_center_command::exec);
    data.put<std::string>("Request.command.name", name);
    data.put<bool>("Request.command.isSet", isSet);

    if (isSet) {
        data.put<int>("Request.command.value", valToSet);
    }

    return data;
}
