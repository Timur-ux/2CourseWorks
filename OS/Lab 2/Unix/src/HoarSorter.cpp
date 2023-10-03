#include "HoarSorter.hpp"

void HoarSorter::sort(Range &&range)
{
    if(range.r - range.l < 2) {
        return;
    }
    int mid = vectorToSort[(range.l + range.r)/2];
    int i = range.l, j = range.r-1;
    do {
        while(vectorToSort[i] < mid) {
            ++i;
        }
        while(vectorToSort[j] > mid) {
            --j;
        }
        if(i <= j) {
            swap(vectorToSort[i], vectorToSort[j]);
            ++i, --j;
        }
    } while (i <= j);
    threader.add((threadFunc)&parallelSort, getWorkerData(new Range(i, range.r)));
    sort(Range(range.l, j));
}

void parallelSort(WorkerData *workerData)
{
    workerData->hoarSorter.sort(move(workerData->range));
    return;
}

HoarSorter::HoarSorter(int threadsCount, string logFile) : 
logger(logFile, string("Threads,Time(ms)")) {
    threader = Threader(threadsCount);
    hronoMeter = HronoMeter();
}

void HoarSorter::run()
{
    hronoMeter.startWatch();
    threader.add((threadFunc)parallelSort, getWorkerData(new Range(0, vectorToSort.size())));
    hronoMeter.stopWatch();

    auto time = hronoMeter.getTime();

    logger.write(to_string(threader.getThreadsCount())
                +string(",")
                +to_string(time.count()));
}

void HoarSorter::setVectorToSort(vector<int> &v)
{
    vectorToSort = v;
}

vector<int> &HoarSorter::getVectorToSort()
{
    return vectorToSort;
}

WorkerData* HoarSorter::getWorkerData(void* range)
{
    WorkerData *result = new WorkerData(*this, *static_cast<Range*>(range));
    return result;
}
