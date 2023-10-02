#include "HoarSorter.hpp"

void HoarSorter::_sort(Range &range)
{
    if(range.r - range.l < 2) {
        return;
    }
    int midIndex = (range.l + range.r)/2;
    int i = range.l, j = range.r - 1;
    do {
        while(i < midIndex and vectorToSort[i] < vectorToSort[midIndex]) {
            ++i;
        }
        while(j > midIndex and vectorToSort[j] > vectorToSort[midIndex]) {
            --j;
        }
        if(i != j) {
            swap(vectorToSort[i], vectorToSort[j]);
            ++i, --j;
        }
    } while (i < j);
    Range range2(i, range.r);
    threader.add((threadFunc)&HoarSorter::_sort, &range);
    range2.l = range.l;
    range2.r = j;
    threader.add((threadFunc)&HoarSorter::_sort, &range);
}

HoarSorter::HoarSorter(int threadsCount, string logFile) : 
logger(logFile, string("Threads,Time(ms)")) {
    threader = Threader(threadsCount);
    hronoMeter = HronoMeter();
}

void HoarSorter::sort(vector<int> &v)
{
    vectorToSort = v;

    hronoMeter.startWatch();
    Range range(0, vectorToSort.size());
    threader.add((threadFunc)&HoarSorter::_sort, &range);
    hronoMeter.stopWatch();

    auto time = hronoMeter.getTime();
    logger.write(to_string(threader.getThreadsCount())
                +string(",")
                +to_string(time.count()));
}
