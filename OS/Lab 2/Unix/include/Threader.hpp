#pragma once

#include <unistd.h>
#include <pthread.h>
#include <stdexcept>

using namespace std;

class Threader {
private:
    int threads_count;
    pthread_t * threads;
    pthread_mutex_t mutex;
public:
    Threader(int _threads_count = 0);
    ~Threader();
    
}