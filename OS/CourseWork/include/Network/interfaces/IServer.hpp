#ifndef I_SERVER_H_
#define I_SERVER_H_

#include "Messages/Message.hpp"
#include "Messages/MessageObserver.hpp"

#include <list>
#include <boost/optional.hpp>

namespace network {
	class IServer : public ::message::IObserver {
	public:
		virtual void startAuth() = 0;
		virtual void stopAuth() = 0;

		virtual boost::optional<long long> getIdByLogin(std::string) = 0;

		virtual void sendForAll(::message::IMessage&) = 0;
		virtual void sendFor(long long id, ::message::IMessage&) = 0;

		virtual void startRecieving() = 0;
		virtual void stopRecieving() = 0;

		virtual std::list<long long> ping(std::list<long long> identificators) = 0; // return bad id

		virtual void subscribe(::message::ISubscriber&) = 0;
		virtual void unsubscribe(::message::ISubscriber&) = 0;
		virtual void notify_all(std::shared_ptr<message::IMessage>) = 0;
	};
} // !network

#endif // !I_SERVER_H_
