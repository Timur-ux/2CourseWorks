#include "HoarSorter.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v{1, 2, 3, 4, 4, 3, 2, 1};
    HoarSorter hsorter(2);
    hsorter.sort(v);
    for(int i : v) 
        cout << i << ' ';
    cout << endl;
    return 0;
}