#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

#include <sys/mman.h>
#include <sys/shm.h>
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

	int fdCond = shm_open(fileCondName.c_str(), O_CREAT | O_RDWR, 0777);
	setFileSize(fdCond, sizeof(pthread_cond_t) + sizeof(pthread_mutex_t) + sizeof(bool) + 1);
	void * mmapCond = openMMap(fdCond
							 , sizeof(pthread_cond_t) + sizeof(pthread_mutex_t) + sizeof(bool)
	);
	memcpy(mmapCond, new pthread_cond_t, sizeof(pthread_cond_t));
	memcpy(mmapCond + mutexPos, new pthread_mutex_t, sizeof(pthread_mutex_t));
	memcpy(mmapCond + statePos, new bool(true), sizeof(bool));

	if (pthread_cond_init(static_cast<pthread_cond_t *>(mmapCond), NULL)) {
		stringstream errorstream;
		errorstream << "Pthread cond init failed, errno = " << errno;
		throw runtime_error(errorstream.str());
	}
	if (pthread_mutex_init(static_cast<pthread_mutex_t *>(mmapCond + mutexPos), NULL)) {
		stringstream errorstream;
		errorstream << "Pthread mutex init failed, errno = " << errno;
		throw runtime_error(errorstream.str());
	}

	int fdData = shm_open(fileDataName.c_str(), O_CREAT | O_RDWR, 0777);
	setFileSize(fdData, (MAX_LEN + 1) * sizeof(int));
	void * mmapData = openMMap(fdData, (MAX_LEN + 1) * sizeof(int));
	int pid = fork();

	if (pid < 0) {
		cerr << "Error MP: fork creating failed" << endl;
	}
	else if (pid == 0) { // Child process
		char * argv[] = { (char *)fileName.c_str()
						, (char *)outputName.c_str()
						, (char *)to_string(fdCond).c_str()
						, (char *)to_string(fdData).c_str()
						,  NULL };

		if (execv(argv[0], argv) == -1) {
			cerr << "Error MP: execv failed, errno " << errno << endl;
		}
	}
	else { // Parent process
		int ints[MAX_LEN]{ 0 };
		while (true) {
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
		close(fdCond);
		close(fdData);
		pthread_cond_destroy(static_cast<pthread_cond_t *>(mmapCond));
		pthread_mutex_destroy(static_cast<pthread_mutex_t *>(mmapCond + mutexPos));
	}
	return 0;
}

FILE * openFile(const char * fileName, const char * mode) {
	FILE * file = fopen(fileName, mode);
	if (file == NULL) {
		stringstream errorstream;
		errorstream << "Can't open " << fileName << " with " << mode << " mode, errno = " << errno;
		throw runtime_error(errorstream.str());
	}

	return file;
}

void setFileSize(int __fd, unsigned long int size) {
	if (ftruncate(__fd, size) < 0) {
		stringstream errorstream;
		errorstream << "Can't set " << size << " size to file with " << __fd << " deskriptor, errno = " << errno;
		throw runtime_error(errorstream.str());
	}
}

void * openMMap(int __fd, unsigned long int size) {
	void * result = mmap(0, size, PROT_WRITE | PROT_READ | PROT_EXEC, MAP_SHARED, __fd, 0);
	if (result == MAP_FAILED) {
		stringstream errorstream;
		errorstream << "Can't create mmap to deskriptor " << __fd << " with size " << size << ", errno = " << errno;
		throw runtime_error(errorstream.str());
	}

	return result;
}
