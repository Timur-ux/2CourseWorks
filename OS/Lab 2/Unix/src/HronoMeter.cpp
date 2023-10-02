#include "HronoMeter.hpp"

HronoMeter::HronoMeter()
{
}

void HronoMeter::startWatch()
{
    start = chrono::steady_clock::now();
    watching = true;
}

void HronoMeter::stopWatch()
{
    if(!watching) {
        throw logic_error("ChronoMeter error: can't stop timer before start");
    }
    end = chrono::steady_clock::now();
    watching = false;
}

chrono::milliseconds HronoMeter::getTime()
{
    if(watching) {
        throw logic_error("ChronoMeter error: can't get time before watching's end");
    }
    return chrono::duration_cast<chrono::milliseconds>(end - start);
}
