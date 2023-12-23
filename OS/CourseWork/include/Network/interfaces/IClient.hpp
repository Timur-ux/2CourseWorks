#ifndef I_CLIENT_H_
#define I_CLIENT_H_

#include "Messages/Message.hpp"
#include "Messages/MessageObserver.hpp"

namespace network {
	class IClient : public message::IObserver {
	public:
		virtual void connect() = 0;
		virtual void disconnect() = 0;

		virtual void auth() = 0;

		virtual void send(message::IMessage) = 0;

		virtual void startRecieving() = 0;
		virtual void stopRecieving() = 0;

		virtual void subscribe(message::ISubscriber&) = 0;
		virtual void unsubscribe(message::ISubscriber&) = 0;
		virtual void notify_all(message::IMessage) = 0;
	};

}

#endif // !I_CLIENT_H_
