#pragma once

#include "Threader.hpp"
#include "MyLogger.hpp"
#include "HronoMeter.hpp"

#include <vector>
#include <stdexcept>

using namespace std;

struct Range {
    int l;
    int r;

    Range(int _l, int _r) : l(_l), r(_r) {}
};

class HoarSorter {
private:
    Threader threader;
    MyLogger logger;
    HronoMeter hronoMeter;
    vector<int> vectorToSort;
    void _sort(Range & range);
    void*(*threadSort)(Range & range);
public:
    HoarSorter(int threadsCount = 1, string logFile = "Log.txt");
    void sort(vector<int> &v);
};