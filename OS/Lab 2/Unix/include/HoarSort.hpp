#pragma once

#include "ThreadPool.hpp"
 
#include <vector>

using namespace std;

struct WorkerData {
    int l;
    int r;
    vector<int> *v;
    ThreadPool * threadPool;
    WorkerData(int _l, int _r, vector<int> *_v, ThreadPool * _threadPool) :
    l(_l), r(_r), v(_v), threadPool(_threadPool) {};
};

void * parallelHoarSort(void * workerData);