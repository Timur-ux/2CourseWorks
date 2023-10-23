#pragma once

#include <chrono>
#include <stdexcept>

using namespace std;

class HronoMeter {
private:
    bool watching = false;
    chrono::milliseconds watchingTime;
    chrono::time_point<chrono::steady_clock> start;
    chrono::time_point<chrono::steady_clock> end;
public:
    void startWatch();
    void stopWatch();
    chrono::milliseconds getTime();
};