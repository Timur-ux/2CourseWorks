#ifndef CLIENT_H_
#define CLIENT_H_

#include "../interfaces/IClient.hpp"
#include "../ports.hpp"

#include <string>
#include <map>
#include <zmq.hpp>

namespace network {
	class Client : public IClient {
	private:
		std::string IP;
		std::map<ports, unsigned short> ports;
		std::map<ports, zmq::socket_t> sockets;
		
	};
}

#endif // !CLIENT_H_