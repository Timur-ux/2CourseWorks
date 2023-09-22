#include <iostream>
#include <unistd.h>
#include <string>
#include <limits.h>
#include <sstream>

#define MAX_LEN 100

using namespace std;

enum PIPE {READ, WRITE};

string readFromChild(int fd);

int main() {
    int fd1[2], fd2[2];
    
    if(pipe(fd1) == -1 || pipe(fd2) == -1) {
        cerr << "Error MP: pipe creating fault" << endl;
    }
    
    string fileName, outputName;

    cout << "Input subprogram name(\"subprogram\" by default): ";
    getline(cin, fileName);
    cout << "Input output file's name(\"Output.txt\" by default): ";
    getline(cin, outputName);
    fileName = (fileName == "" || fileName.size() > PATH_MAX ? "subprogram" : fileName);
    outputName = (outputName == "" || outputName.size() > PATH_MAX ? "Output.txt" : outputName);

    cout << "Input \"num1 num2 ...<endline>\" as command" << endl;
    cout << "Input \"Exit\" for exit" << endl;

    int pid = fork();
    
    if( pid < 0 ) {
        cerr << "Error MP: fork creating failed" << endl;
    } else if( pid == 0 )  { // Child process
        close(fd1[WRITE]);
        close(fd2[READ]);
        if( dup2(fd1[READ], fileno(stdin)) != 0) {
            cerr << "Error MP: dup2 failed" << endl;
        }
        char * argv[] = {(char*)fileName.c_str(), (char *)outputName.c_str(), NULL};
        if( execv(argv[0], argv) == -1) {
            cerr << "Error MP: execv failed" << endl;
        }
    } else { // Parent process
        close(fd1[READ]);
        close(fd2[WRITE]);
        if( write(fd1[WRITE], &fd2[WRITE], sizeof(int)) != sizeof(int)) { // send to child a pipe's write-end
            cerr << "Error MP: write failed" << endl;
        }
        int iarr[MAX_LEN];
        while( true ) {
            string command;
            int i = 0, num;
            getline(cin, command);
            stringstream ss(command, ios_base::in);
            while(command != "Exit" and (ss >> num)) {
                if(i >= MAX_LEN) {
                    cerr << "Error: string must have " << MAX_LEN << " numbers max" << endl;
                }
                iarr[i] = num;
                ++i;
            }

            if(command == "Exit") {
                int exitcode = -1;
                if(write(fd1[WRITE], &exitcode, sizeof(int)) != sizeof(int)) {
                    cout << "Error MP: write to pipe failed" << endl;
                }
                break;
            }

            if(write(fd1[WRITE], &i, sizeof(int)) != sizeof(int) || 
                write(fd1[WRITE], iarr, sizeof(int)*i) != sizeof(int)*i ) {
                cout << "Error MP: write to pipe failed" << endl;
            }
    
            string childReport = readFromChild(fd2[READ]);
            cout << childReport << endl;
        }

        close(fd1[WRITE]);
        close(fd2[READ]);
    }
    return 0;
}

string readFromChild(int fd) {
    int len;
    if( read(fd, &len, sizeof(int)) != sizeof(int) ) {
        cerr << "Error MP: read failed" << endl;
    }
    char buff[len+1];
    if( read(fd, buff, len) != len) {
        cerr << "Error MP: read failed" << endl;
    }
    buff[len] = '\0';
    return buff;
}
