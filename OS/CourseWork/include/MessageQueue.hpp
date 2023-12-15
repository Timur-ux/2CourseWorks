#ifndef MESSAGE_QUEUE_H_
#define MESSAGE_QUEUE_H_

#include <queue>
#include <shared_mutex>

template <typename TMessage>
class MessageQueue {
private:
    std::queue<TMessage> mq;
    mutable std::shared_mutex mutex;
public:
    void push(TMessage message);
    void pop();
    TMessage front() const;
    bool empty() const;
    size_t size() const;
};

template<typename TMessage>
inline void MessageQueue<TMessage>::push(TMessage message) {
    std::unique_lock<std::shared_mutex> lock(mutex);
    mq.push(message);
}

template<typename TMessage>
inline void MessageQueue<TMessage>::pop() {
    std::unique_lock<std::shared_mutex> lock(mutex);
    mq.pop();
}

template<typename TMessage>
inline TMessage MessageQueue<TMessage>::front() const {
    std::shared_lock<std::shared_mutex> lock(mutex);
    return mq.front();
}

template<typename TMessage>
inline bool MessageQueue<TMessage>::empty() const {
    std::shared_lock<std::shared_mutex> lock(mutex);
    return mq.empty();
}

template<typename TMessage>
inline size_t MessageQueue<TMessage>::size() const {
    std::shared_lock<std::shared_mutex> lock(mutex);

    return mq.size();
}

#endif




