#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include <sstream>

#include "Client.hpp"
#include "bufferSize.hpp"
#include "CalcCenterCommands.hpp"



int main(int argc, char * argw[]) {
    if (argc != 3) {
        throw std::invalid_argument("Error: invalid input parameters. Usage: <program name> <server IP> <server port>");
    }

    std::map<std::string, int> dict;

    std::string serverIP = argw[1];
    unsigned int serverPort = atoi(argw[2]);

    Client client(serverIP, serverPort);

    int errorsCount = 0;
    while (errorsCount < 100) {
        std::vector<char> request;
        try {
            request = client.recieve();
        }
        catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            ++errorsCount;
        }
        errorsCount = 0;

        std::stringstream commandStream(request.data());

        std::string command;
        commandStream >> command;

        if (command == calc_center_command::terminate) {
            break;
        }
        else if (command == calc_center_command::exec) {
            std::string name;
            int value;
            commandStream >> name;
            if (commandStream >> value) {
                dict[name] = value;
                client.sendData(strToVChar(calc_center_return::execSucceed));
            }
            else {
                std::stringstream response;
                if (dict.find(name) == dict.end()) {
                    response << calc_center_return::notFound;
                }
                else {
                    response << calc_center_return::execSucceed << ':' << dict[name];
                }
                client.sendData(strToVChar(response.str()));
            }
        }
    }

    return 0;
}