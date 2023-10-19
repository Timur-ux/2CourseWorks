#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>
#include <limits.h>
#include <fcntl.h>

#define MAX_LEN 100

using namespace std;

FILE * openFile(const char * fileName, const char * mode);
void setFileSize(int __fd, unsigned long int size);
void * openMMap(int __fd, unsigned long int size);

int main() {

	string fileName, outputName;
	string fileCondName = "fileCond";
	string fileDataName = "fileData";

	int mutexPos = sizeof(pthread_cond_t);
	int statePos = mutexPos + sizeof(pthread_mutex_t);

	cout << "Input subprogram name(\"subprogram\" by default): ";
	getline(cin, fileName);
	cout << "Input output file's name(\"Output.txt\" by default): ";
	getline(cin, outputName);
	fileName = (fileName == "" || fileName.size() > PATH_MAX ? "subprogram" : fileName);
	outputName = (outputName == "" || outputName.size() > PATH_MAX ? "Output.txt" : outputName);

	cout << "Input \"num1 num2 ...<endline>\" as command" << endl;
	cout << "Input \"Exit\" for exit" << endl;

	int fileCond = open(fileName.c_str(), O_CREAT | O_RDWR | O_TRUNC);//openFile(fileCondName.c_str(), "w");
	setFileSize(fileCond, sizeof(pthread_cond_t) + sizeof(pthread_mutex_t) + sizeof(bool) + 1);
	void * mmapCond = openMMap(fileCond, sizeof(pthread_cond_t) + sizeof(pthread_mutex_t) + sizeof(bool));
	int * pint = new int(25);
	memcpy(mmapCond, pint, sizeof(int));
	cout << *(int *)mmapCond << endl;
	close(fileCond);
	return 0;
	memcpy(mmapCond, new pthread_cond_t, sizeof(pthread_cond_t));
	memcpy(mmapCond + mutexPos, new pthread_mutex_t, sizeof(pthread_mutex_t));
	memcpy(mmapCond + statePos, new bool(true), sizeof(bool));

	pthread_cond_init(static_cast<pthread_cond_t *>(mmapCond), NULL);
	pthread_mutex_init(static_cast<pthread_mutex_t *>(mmapCond + mutexPos), NULL);

	int fileData = open(fileName.c_str(), O_CREAT | O_RDWR | O_TRUNC);;
	setFileSize(fileData, (MAX_LEN + 1) * sizeof(int));
	void * mmapData = openMMap(fileData, (MAX_LEN + 1) * sizeof(int));


	int pid = fork();

	if (pid < 0) {
		cerr << "Error MP: fork creating failed" << endl;
	}
	else if (pid == 0) { // Child process
		char * argv[] = { (char *)fileName.c_str()
						, (char *)outputName.c_str()
						, (char *)to_string(fileCond).c_str()
						, (char *)to_string(fileData).c_str()
						,  NULL };

		if (execv(argv[0], argv) == -1) {
			cerr << "Error MP: execv failed" << endl;
		}
	}
	else { // Parent process
		int ints[MAX_LEN]{ 0 };
		while (true)
		{
			string command;
			int i = 0, num;
			getline(cin, command);
			stringstream ss(command, ios_base::in);
			while (command != "Exit" and (ss >> num)) {
				if (i >= MAX_LEN) {
					cerr << "Error: string must have " << MAX_LEN << " numbers max" << endl;
				}
				ints[i] = num;
			}

			if (command == "Exit") {
				*static_cast<bool *>(mmapCond + statePos) = false;
				pthread_cond_signal(static_cast<pthread_cond_t *>(mmapCond));
				break;
			}

			memcpy(mmapData, ints, MAX_LEN * sizeof(int));
			pthread_cond_signal(static_cast<pthread_cond_t *>(mmapCond));
		}
		close(fileCond);
		close(fileData);
	}
	return 0;
}

FILE * openFile(const char * fileName, const char * mode) {
	FILE * file = fopen(fileName, mode);
	if (file == NULL) {
		stringstream errorstream;
		errorstream << "Can't open " << fileName << " with " << mode << " mode";
		throw runtime_error(errorstream.str());
	}

	return file;
}

void setFileSize(int __fd, unsigned long int size) {
	if (lseek(__fd, size, SEEK_SET) < 0) {
		stringstream errorstream;
		errorstream << "Can't set " << size << " size to file with " << __fd << " deskriptor";
		throw runtime_error(errorstream.str());
	}
}

void * openMMap(int __fd, unsigned long int size) {
	void * result;
	if ((result = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, __fd, 0)) == MAP_FAILED) {
		stringstream errorstream;
		errorstream << "Can't create mmap to deskriptor " << __fd << " with size " << size;
		throw runtime_error(errorstream.str());
	}

	return result;
}
