#include "HoarSort.hpp"

void * parallelHoarSort(void * workerData) {

    WorkerData thisData = *static_cast<WorkerData*>(workerData);
    WorkerData *otherData;

    if(thisData.r - thisData.l < 2) {
        return NULL;
    }
    int mid = thisData.v->at((thisData.l + thisData.r)/2);
    int i = thisData.l, j = thisData.r - 1;
    do {
        while(thisData.v->at(i) < mid) {
            ++i;
        }
        while(thisData.v->at(j) > mid) {
            --j;
        }
        if(i <= j) {
            swap(thisData.v->at(i), thisData.v->at(j));
            ++i, --j;
        }
    } while (i <= j);

    otherData = new WorkerData(i, thisData.r, thisData.v, thisData.threadPool);
    thisData.threadPool->addTask(Task((threadFunc)&parallelHoarSort, otherData));
    
    thisData.r = j + 1;
    parallelHoarSort(&thisData);
    
    return NULL;
}