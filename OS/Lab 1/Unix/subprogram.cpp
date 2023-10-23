#include <iostream>
#include <unistd.h>
#include <string>

using namespace std;

int calc(const string & s) {
    int result = 0, temp = 0;
    for (char c : s)
    {
        if(c == ' ') {
            result += temp;
            temp = 0;
            continue;
        }
        temp = temp*10 + (c - '0');
    }
    result += temp;
    return result;
}
void writeToParent(int fd, const string &s) {
    int len = s.size();
    if( write(fd, &len, sizeof(int)) != sizeof(int)  ||
        write(fd, s.c_str(), len) != len) {
                cerr << "Error SP: write failed" << endl;
    }
}
int main(int argc, char * argv[]) {
    
    if(argc < 2) {
        cerr << "Error SP: no ouput file's name given" << endl;
    }

    int writeFD;
    if(read(fileno(stdin), &writeFD, sizeof(int)) != sizeof(int)) { // read pipe's write-end
        cerr << "Error SP: read input FD failed" << endl;
    }

    FILE * outFile = fopen(argv[1], "w");

    if( dup2(fileno(outFile), fileno(stdout)) == -1 ) {
        cerr << "Error SP: dup2 failed" << endl;
    }
    
    while(true) {
        string report;
        int nCount, result = 0;
        if( read(fileno(stdin), &nCount, sizeof(int)) != sizeof(int)) {
            cerr << "Error: read failed" << endl;
        } 
        if(nCount == 0) {
            report = "Out: clear string, nothing to calc";
            writeToParent(writeFD, report);
            continue;
        }
        if(nCount == -1) { // Parent gone
            break;
        }
        for(int i = 0; i < nCount; ++i) {
            int temp;
            if( read(fileno(stdin), &temp, sizeof(int)) != sizeof(int) ) {
                cerr << "Error: read failed" << endl;
            }
            result += temp;
        }

        cout << result << endl;

        report = "Out: done";
        writeToParent(writeFD, report);
    }

    fclose(outFile);
    close(writeFD);
}