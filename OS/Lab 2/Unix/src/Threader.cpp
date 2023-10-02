#include "Threader.hpp"

int Threader::setNextThreadId()
{
    currentThreadId = (currentThreadId + 1 ) % threadsCount;
    return currentThreadId;
}

Threader::Threader(int _threadsCount) : threadsCount(_threadsCount)
{
    threads = new pthread_t[threadsCount];
    if( pthread_mutex_init(&mutex, NULL) != 0) {
        throw runtime_error("Mutex initialization error");
    }
}

Threader::~Threader()
{
    delete [] threads;
    pthread_mutex_destroy(&mutex);
}

void Threader::enableMutex()
{
    if( pthread_mutex_lock(&mutex) != 0 ) {
        throw runtime_error("Mutex locking error");
    }
}

void Threader::disableMutex()
{
    if( pthread_mutex_unlock(&mutex) != 0 ) {
        throw runtime_error("Mutex unlocking error");
    }
}

void Threader::add(void *(*start)(void *), void *arg)
{
    setNextThreadId();
    pthread_create(&threads[currentThreadId], NULL, start, arg);
    pthread_join(threads[currentThreadId], NULL);
}

int Threader::getThreadsCount()
{
    return threadsCount;
}
