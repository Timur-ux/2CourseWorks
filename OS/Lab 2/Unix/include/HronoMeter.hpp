#pragma once

#include <chrono>
#include <stdexcept>

using namespace std;

class HronoMeter {
private:
    bool watching = false;
    retType watchingTime = NULL;
public:
    HronoMeter();
    void start();
    void stop();
    retType getTime();
}