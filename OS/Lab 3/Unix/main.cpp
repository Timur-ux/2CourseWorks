#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>

#include <sys/mman.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_LEN 100

using namespace std;

int openShmFile(const char * fileName);
void setFileSize(int __fd, unsigned long int size);
void * openMMap(int __fd, unsigned long int size);

int main() {

	string fileName, outputName;
	string fileDataName = "fileData";
	string fileMutexName = "fileMutex";

	cout << "Input subprogram name(\"subprogram\" by default): ";
	getline(cin, fileName);
	cout << "Input output file's name(\"Output.txt\" by default): ";
	getline(cin, outputName);
	fileName = (fileName == "" || fileName.size() > PATH_MAX ? "subprogram" : fileName);
	outputName = (outputName == "" || outputName.size() > PATH_MAX ? "Output.txt" : outputName);

	cout << "Input \"num1 num2 ...<endline>\" as command" << endl;
	cout << "Input \"Exit\" for exit" << endl;

	int fdMutex = openShmFile(fileMutexName.c_str());
	setFileSize(fdMutex, sizeof(pthread_mutex_t));
	pthread_mutex_t * mutex = (pthread_mutex_t *)openMMap(fdMutex, sizeof(pthread_mutex_t));
	pthread_mutexattr_t * mutexattr = (pthread_mutexattr_t *)malloc(sizeof(pthread_mutexattr_t));
	if (pthread_mutexattr_setpshared(mutexattr, PTHREAD_PROCESS_SHARED)) {
		throw invalid_argument("Mutexattr set failed");
	}
	if (pthread_mutex_init(mutex, mutexattr)) {
		throw invalid_argument("Mutex init failed");
	}

	int fdData = openShmFile(fileDataName.c_str());
	setFileSize(fdData, (MAX_LEN + 1) * sizeof(int));
	int * data = (int *)openMMap(fdData, (MAX_LEN + 1) * sizeof(int));

	int pid = fork();

	if (pid < 0) {
		cerr << "Error MP: fork creating failed" << endl;
	}
	else if (pid == 0) { // Child process
		char * argv[] = { (char *)fileName.c_str()
						, (char *)outputName.c_str()
						, (char *)fileDataName.c_str()
						,  NULL };

		if (execv(argv[0], argv) == -1) {
			cerr << "Error MP: execv failed, errno " << errno << endl;
		}
	}
	else { // Parent process
		string command;
		while (true) {
			pthread_mutex_lock(mutex);
			int ints[MAX_LEN]{ 0 };
			int i = 0, num;

			getline(cin, command);
			stringstream ss(command, ios_base::in);
			while (command != "Exit" and (ss >> num)) {
				if (i >= MAX_LEN) {
					stringstream errorstream;
					errorstream << "Error: string must have " << MAX_LEN << " numbers max" << endl;
					throw runtime_error(errorstream.str());
				}
				ints[i++] = num;
			}

			if (command == "Exit") {
				ints[0] = -111333666;
				memcpy(data, ints, MAX_LEN * sizeof(int));
				break;
			}

			memcpy(data, ints, MAX_LEN * sizeof(int));
			pthread_mutex_unlock(mutex);
		}
		wait(NULL);
		if (shm_unlink(fileDataName.c_str()) == -1) {
			throw runtime_error("shm_unlink error on file data");
		}
	}
	return 0;
}

int openShmFile(const char * fileName) {
	int file = shm_open(fileName, O_CREAT | O_RDWR, 0777);
	if (file == -1) {
		stringstream errorstream;
		errorstream << "Can't open " << fileName << " with " << 0777 << " mode, errno = " << errno;
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
