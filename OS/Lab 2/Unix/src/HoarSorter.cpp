#include "HoarSorter.hpp"

void HoarSorter::_sort(int l, int r)
{
    if(r - l < 2) {
        return;
    }
    int midIndex = (l+r)/2;
    int i = l, j = r-1;
    do {
        while(i < midIndex and vectorToSort[i] < vectorToSort[midIndex]) {
        ++i;
        }
        while(j > midIndex and vectorToSort[j] > vectorToSort[midIndex]) {
            --j;
        }
        if(i != j) {
            swap(vectorToSort[i], vectorToSort[j]);
            ++i;
            --j;
        }
    } while (i < j);
    //threader.add(_sort(i, r))
    //threader.add(_sort(l, j))
}

HoarSorter::HoarSorter(int threads_count = 1, string logFile)
{
    threader = Threader(threads_count);
    logger = Logger(logFile, "Threads,Time");
    hronoMeter = HronoMeter();
}

void HoarSorter::sort(vector<int> &v)
{
    vectorToSort = v;

    hronoMeter.start();
    // threader.add(_sort(0, vectorToSort.size()));
    hronoMeter.stop();

    auto time = hronoMeter.getTime();
    logger.write(string(threads_count)
                +string(",")
                +string(time));
}
