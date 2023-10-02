#pragma once

#include <unistd.h>
#include <pthread.h>
#include <stdexcept>

using namespace std;

typedef void* (*threadFunc)(void *);

class Threader {
private:
    int threadsCount;
    pthread_t * threads;
    pthread_mutex_t mutex;
    int currentThreadId = 0;
    int setNextThreadId();
public:
    Threader(int _threadsCount = 0);
    ~Threader();
    void enableMutex();
    void disableMutex();
    void add(void *(*start)(void *), void* arg);
    int getThreadsCount();
};