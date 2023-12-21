#ifndef SOCKET_H_
#define SOCKET_H_

#include <string>

struct Socket {
	std::string IP;
	unsigned short port;

	Socket(std::string _IP, unsigned short _port) : IP(_IP), port(_port) {}
	Socket(std::string strSocket) {
		std::string _IP;
		unsigned short _port;

		bool portSetted = false;
		for (i = 0; i < strSocket.size(); ++i) {
			if (strSocket[i] == ':') {
				_port = atoi(strSocket.substr(i + 1, strSocket.size() - i - 1).c_str());
				portSetted = true;
				break;
			}
			_IP += strSocket[i];
		}

		if (!portSetted) {
			throw std::invalid_argument("Bad string socket representation. Given: " + strSocket);
		}

		IP = _IP;
		port = _port;
	}
};

#endif