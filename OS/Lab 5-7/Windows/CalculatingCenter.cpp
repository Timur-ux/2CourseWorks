#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include <sstream>

#include "Client.hpp"
#include "CalcCenterCommands.hpp"

int main(int argc, char * argw[]) {
    if (argc != 5) {
        throw std::invalid_argument("Usage: <program name> <server IP> <server port 1> <server port 2> <id>");
    }

    std::map<std::string, int> dict;

    std::string serverIP = argw[1];
    unsigned short serverPort1 = atoi(argw[2]);
    unsigned short serverPort2 = atoi(argw[3]);
    long long id = atoi(argw[4]);

    Client client(serverIP, serverPort1, serverPort2, id);

    while (true) {
        pt::ptree request = client.recieve();
        pt::ptree response;

        std::string type = request.get<std::string>("Request.type");

        response.put<std::string>("Response.type", type);
        
        if (type == calc_center_command::exec) {
            std::string name = request.get<std::string>("Request.command.name");
            bool isSet = request.get<bool>("Request.command.isSet");

            if (isSet) {
                int value = request.get<int>("Request.command.value");
                dict[name] = value;

                response.put<std::string>("Response.execType", "SetValue");
            }
            else {
                response.put<std::string>("Response.execType", "GetValue");
                auto nameIt = dict.find(name);
                if (nameIt == std::end(dict)) {
                    response.put<bool>("Response.found", false);
                }
                else {
                    response.put<int>("Response.value", nameIt->second);
                    response.put<bool>("Response.found", true);
                }
            }
            response.put<std::string>("Response.status", calc_center_return::execSucceed);
        }
        else if (type == calc_center_command::ping) {
            response.put<std::string>("Response.status", calc_center_return::execSucceed);
        }
        else if (type == calc_center_command::terminate) {
            return 0;
        }
        else {
            continue;
        }

        client.sendData(response);
    }

    return 0;
}