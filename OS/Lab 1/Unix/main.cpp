#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string>

using namespace std;

enum PIPE {READ, WRITE};

int main() {
    int fd1[2], fd2[2];
    
    if(pipe(fd1) == -1 || pipe(fd2) == -1) {
        cerr << "Error: pipe creating fault" << endl;
    }
    
    string fileName;
    cout << "Input subprogram name(\"subprogram\" by default): ";
    getline(cin, fileName);

    cout << "Input \"num1 num2 ...\" as command" << endl;
    cout << "Input \"Exit\" for exit" << endl;

    int pid = fork();
    
    if( pid < 0 ) {
        cerr << "Error: fork creating error" << endl;
    } else if( pid == 0 )  { // Child process
        close(fd1[WRITE]);
        close(fd2[READ]);
        char * argv[] = {(char *)fileName.c_str(), (char *)to_string(fd2[WRITE]).c_str(),
                        (char*)to_string(fd1[READ]).c_str()};
        execv(argv[0], argv);
    } else { // Parent process
        close(fd1[READ]);
        close(fd2[WRITE]);
        while( true ) {
            string command;
            getline(cin, command);
            int len = command.size();
            if( write(fd1[WRITE], &len, sizeof(int)) != sizeof(int) ||
            write(fd1[WRITE], command.c_str(), len) != len) {
                cout << "Error: write to pipe failed" << endl;
            }
            if(command == "Exit")
                break;
            char childReport[4];
            read(fd2[READ], childReport, 4);
            cout << childReport << endl;
        }

        close(fd1[WRITE]);
        close(fd2[READ]);
    }
    return 0;
}