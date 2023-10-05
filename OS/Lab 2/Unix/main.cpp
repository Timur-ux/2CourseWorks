#include "HoarSort.hpp"
#include "Logger.hpp"
#include "ThreadPool.hpp"
#include "HronoMeter.hpp"

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;


int main() {
    const int n = 10000000;
    vector<int> v(n);
    for(int &i : v) {
        i = rand()%100;
    }
    
    HronoMeter hronoMeter;
    Logger logger("Log.txt", NEW, "Threads,Time(ms)");
    for(int threadsCount = 1; threadsCount <= 8; threadsCount++)
    {
        for(int _ = 0; _ < 1; ++_) {
            vector<int> copyV = v;
            {
                ThreadPool threadPool(threadsCount);
                WorkerData workerData{0, static_cast<int>(v.size()), &copyV, &threadPool};

                // todo попробовать семафор жахнуть, вместо счётчика.

                hronoMeter.startWatch();
                parallelHoarSort(&workerData);
            }
            hronoMeter.stopWatch();
            auto time = hronoMeter.getTime();
            logger.write( to_string(threadsCount) 
                        + string(",")
                        + to_string(time.count()));

            bool assertResult = true;
            for(int i = 1; i < copyV.size(); ++i) {
                if(copyV[i] < copyV[i-1]){
                    assertResult = false;
                    break;
                }
            }
            cout << "Is vector sorted correctly? -- "<< boolalpha << assertResult << endl;
        }
    }
    return 0;
}