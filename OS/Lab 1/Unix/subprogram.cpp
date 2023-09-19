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

int main(int argc, char * argv[]) {
    
    if(argc < 2) {
        cerr << "Error: no ouput file's name given" << endl;
    }

    int writeFD;
    read(fileno(stdin), &writeFD, sizeof(int)); // read pipe's write-end
    
    FILE * outFile = fopen(argv[1], "w");
    dup2(fileno(outFile), fileno(stdout));
    while(true) {
        string command;
        getline(cin, command);
        if(command == "Exit") {
            break;
        }
        int result = calc(command);
        cout << result << endl;
        write(writeFD, "Done", 4);
    }
    fclose(outFile);
    close(writeFD);
}