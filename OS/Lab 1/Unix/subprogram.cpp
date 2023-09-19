#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include <cstddef>

using namespace std;

enum PIPES {READ, WRITE};

int calc(const char * s, int len) {
    int result = 0, temp = 0;
    for (size_t i = 0; i < len; ++i)
    {
        if(s[i] == ' ') {
            result += temp;
            temp = 0;
            continue;
        }
        temp = temp*10 + (s[i]-'0');
    }
    result += temp;
    return result;
}

bool isExit(const char * s) {
    const char * exitCommand = "Exit";
    for(int i = 0; i < 4; ++i) {
        if(s[i] != exitCommand[i]) {
            return false;
        }
    }
    return true;
}

int main(int argc, char * argv[]) {
    if(argc < 3) {
        cerr << "Error: no input/output file descritors given" << endl;
    }
    
    int writeFD = atoi(argv[1]);
    int readFD = atoi(argv[2]);

    cout << "SP is running..." << endl;
    
    FILE * outFile = fopen("Output.txt", "w");
    dup2(readFD, fileno(stdin));
    dup2(fileno(outFile), fileno(stdout));
    while(true) {
        int len;
        char command[256];   
        if(read(readFD, &len, sizeof(int)) != sizeof(int) || read(readFD, command, len) != len ||
            isExit(command)) {
            break;
        }
        int result = calc(command, len);
        cout << result << endl;
        write(writeFD, "Done", 4);
    }
    fclose(outFile);
    close(writeFD);
    close(readFD);
}