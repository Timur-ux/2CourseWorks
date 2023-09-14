#include <iostream>
#include <unistd.h>
#include <string>

using namespace std;

enum PIPES {READ, WRITE};

int main(int argc, char * argw[]) {
    if(argc < 3) {
        cerr << "Error: no input/output file descritors given" << endl;
    }
    
    int inputFD = atoi(argv[1]);
    int outputFD = atoi(argv[2]);
}