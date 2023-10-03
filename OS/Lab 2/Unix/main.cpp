#include "HoarSorter.hpp"

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;


int main() {
    const int n = 1000;
    vector<int> v(n);
    for(int &i : v) {
        i = rand()%100;
    }
    HoarSorter hsorter(4);
    hsorter.setVectorToSort(v);
    hsorter.run();
    vector<int> & result = hsorter.getVectorToSort();
    bool assertResult = true;
    for(int i = 1; i < result.size(); ++i) {
        if(result[i] < result[i-1]){
            assertResult = false;
            break;
        }
    }
    cout << boolalpha << assertResult << endl;
    return 0;
}