#pragma once

#include <unistd.h>
#include <pthread.h>
#include <stdexcept>
#include <queue>
#include <ctime>

using namespace std;

typedef void* (*threadFunc)(void *);

class Task;

static int counter = 0;

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
    void closeAll();
    bool isTasksEmpty();
    ~ThreadPool();
};

void * workerRun(void * _pool);

class Task {
private:
    threadFunc func;
    void * workerData;
public:
    Task(threadFunc _func, void * _workerData) :
        func(_func), workerData(_workerData) {};
    void operator()();
};