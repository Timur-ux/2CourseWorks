#ifndef PORTS_H_
#define PORTS_H_

namespace network {
	enum class ports {
		auth
		, send
		, recv
	};

	struct PortsTriplet {
		unsigned short port1;
		unsigned short port2;
		unsigned short port3;
	};
}

#endif // !PORTS_H_
