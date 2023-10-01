#pragma once

#include "Threader.hpp"
#include "Logger.hpp"
#include "HronoMeter.hpp"

#include <vector>
#include <stdexcept>

using namespace std;

class HoarSorter {
private:
    Threader & threader;
    Logger & logger;
    HronoMeter & hronoMeter;
    vector<int> & vectorToSort;
    void _sort(int l, int r);
public:
    HoarSorter(int threads_count = 1, string logFile = "Log.txt");
    void sort(vector<int> &v);
}