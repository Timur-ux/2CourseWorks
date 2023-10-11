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
    Logger logger("Log.csv", NEW, "Threads,Time(ms),Elements");
    for(int threadsCount = 1; threadsCount <= 8; threadsCount++)
    {
        vector<int> copyV = v;

        ThreadPool threadPool(threadsCount);
        WorkerData workerData{0, static_cast<int>(v.size()), &copyV, &threadPool};

        hronoMeter.startWatch();
        parallelHoarSort(&workerData);
        threadPool.waitAll();
        hronoMeter.stopWatch();
        
        auto time = hronoMeter.getTime();
        logger.write( to_string(threadsCount) 
                    + string(",")
                    + to_string(time.count())
                    + string(",")
                    + to_string(n));

        bool assertResult = true;
        for(int i = 1; i < copyV.size(); ++i) {
            if(copyV[i] < copyV[i-1]){
                assertResult = false;
                break;
            }
        }
        cout << "Is vector sorted correctly? -- "<< boolalpha << assertResult << endl;
    }
    return 0;
}