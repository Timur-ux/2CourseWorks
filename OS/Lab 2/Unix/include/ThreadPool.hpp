#pragma once

#include <unistd.h>
#include <pthread.h>
#include <stdexcept>
#include <queue>
#include <ctime>

using namespace std;

typedef void* (*threadFunc)(void *);

class Task;

class Worker;

class ThreadPool {
private:
    bool isStopped;
    
    friend void* workerRun(void*);
    vector<pthread_t> workers;

    pthread_cond_t cond;
    pthread_mutex_t queue_mutex;

    queue<Task> tasks;
    Task getTask();
public:
    ThreadPool(int workersCount);
    void addTask(Task && task);
    void waitAll();
    bool isTasksEmpty();
    ~ThreadPool();

    pthread_cond_t waitCond;
    pthread_mutex_t waitMutex;
};

void * workerRun(void * _pool);

class Task {
private:
    threadFunc func;
    void * workerData;
public:
    Task(threadFunc _func, void * _workerData) :
        func(_func), workerData(_workerData) {};
    void operator()(ThreadPool & pool);
};