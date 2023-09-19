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
    write(fd, &len, sizeof(int));
    write(fd, s.c_str(), len);
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
        string command, report;
        getline(cin, command);
        if(command == "") {
            report = "Out: clear string, nothing to calc";
            writeToParent(writeFD, report);
            continue;
        }
        if(command == "Exit") {
            break;
        }
        int result = calc(command);
        cout << result << endl;

        report = "Out: done";
        writeToParent(writeFD, report);
    }
    fclose(outFile);
    close(writeFD);
}