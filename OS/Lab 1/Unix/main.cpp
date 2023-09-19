#include <iostream>
#include <unistd.h>
#include <string>

using namespace std;

enum PIPE {READ, WRITE};

string readFromChild(int fd);

int main() {
    int fd1[2], fd2[2];
    
    if(pipe(fd1) == -1 || pipe(fd2) == -1) {
        cerr << "Error: pipe creating fault" << endl;
    }
    
    string fileName, outputName;

    cout << "Input subprogram name(\"subprogram\" by default): ";
    getline(cin, fileName);
    cout << "Input output file's name(\"Output.txt\" by default): ";
    getline(cin, outputName);
    fileName = (fileName == "" ? "subprogram" : fileName);
    outputName = (outputName == "" ? "Output.txt" : outputName);

    cout << "Input \"num1 num2 ...<endline>\" as command" << endl;
    cout << "Input \"Exit\" for exit" << endl;

    int pid = fork();
    
    if( pid < 0 ) {
        cerr << "Error: fork creating error" << endl;
    } else if( pid == 0 )  { // Child process
        close(fd1[WRITE]);
        close(fd2[READ]);
        dup2(fd1[READ], fileno(stdin));
        char * argv[] = {(char*)fileName.c_str(), (char *)outputName.c_str(), NULL};
        execv(argv[0], argv);
    } else { // Parent process
        close(fd1[READ]);
        close(fd2[WRITE]);
        write(fd1[WRITE], &fd2[WRITE], sizeof(int)); // send to child a pipe's write-end
        while( true ) {
            string command;
            getline(cin, command);
            command += '\n';
            if(write(fd1[WRITE], command.c_str(), command.size()) != command.size()) {
                cout << "Error: write to pipe failed" << endl;
            }
            if(command == "Exit\n") {
                break;
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
    read(fd, &len, sizeof(int));
    char buff[len+1];
    read(fd, buff, len);
    buff[len] = '\0';
    return buff;
}