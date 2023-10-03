#pragma once

#include "Threader.hpp"
#include "Logger.hpp"
#include "HronoMeter.hpp"
#include "Parallelable.hpp" 

#include <vector>
#include <stdexcept>
#include <iostream>

using namespace std;

struct Range {
    int l;
    int r;

    Range(int _l, int _r) : l(_l), r(_r) {}
    Range(Range & range) : l(range.l), r(range.r) {}
};

class HoarSorter : public Parallelable {
private:
    Threader threader;
    Logger logger;
    HronoMeter hronoMeter;
    vector<int> vectorToSort;
    void*(*threadSort)(void*);
public:
    HoarSorter(int threadsCount = 1, string logFile = "Log.txt");
    void setVectorToSort(vector<int> &v);
    vector<int> & getVectorToSort();
    void run();
    WorkerData* getWorkerData(void*) override;
    void sort(Range && range);
};

void parallelSort(WorkerData * workerData);

struct WorkerData {
    HoarSorter & hoarSorter;
    Range range;

    WorkerData(HoarSorter & _hoarSorter, Range & _range) :
    hoarSorter(_hoarSorter), range(_range) {};
};