#ifndef OBSERVER_H_
#define OBSERVER_H_

struct ObserverData {
	SOCKET socket = 0;
	long long id = 0;
};

struct ISockSubscriber {
	virtual void update(ObserverData socket) = 0;
};

struct ISockObserver {
	virtual void subscribe(ISockSubscriber *subscriber) = 0;
	virtual void notify_all(ObserverData socket) = 0;
};


#endif