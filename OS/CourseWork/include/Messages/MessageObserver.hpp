#ifndef MESSAGE_OBSERVER_H_
#define MESSAGE_OBSERVER_H_

#include "Message.hpp"

namespace message {
	class IObserver;
	class ISubscriber {
	public:
		virtual void notify(std::shared_ptr<IMessage>) = 0;
		virtual void subscribeTo(IObserver*) = 0;
	};

	class IObserver {
	public:
		virtual void subscribe(ISubscriber&) = 0;
		virtual void unsubscribe(ISubscriber&) = 0;

		virtual void notify_all(std::shared_ptr<IMessage>) = 0;
	};

} // !message

#endif // !MESSAGE_OBSERVER_H_
