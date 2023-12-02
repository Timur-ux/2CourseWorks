#ifndef MESSAGE_QUEUE_H_
#define MESSAGE_QUEUE_H_

#include <string>
#include <mutex>
#include <queue>

struct Message;
enum class RequestType;
class MessageQueue {
private:
	std::queue<Message> queue;
	std::mutex mutex;
public:
	MessageQueue() = default;

	void push(Message message);
	void pop();
	Message front();
};

struct Message {
	RequestType type;
	std::string data;
	SOCKET* sender;
	SOCKET* reciever;
	Message(RequestType _type, std::string _data) : type(_type), data(_data) {}
};
#endif // !MESSAGE_QUEUE_H_
