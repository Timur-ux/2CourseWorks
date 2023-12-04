#ifndef OBSERVER_H_
#define OBSERVER_H_

struct ISockSubscriber {
	virtual void update(SOCKET socket) = 0;
};

struct ISockObserver {
	virtual void subscribe(ISockSubscriber *subscriber) = 0;
	virtual void notify_all(SOCKET socket) = 0;
};



#endif