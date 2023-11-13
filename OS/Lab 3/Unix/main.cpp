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

	cout << "Input subprogram name(\"03_OSLabs_subprogram\" by default): ";
	getline(cin, fileName);
	cout << "Input output file's name(\"Output.txt\" by default): ";
	getline(cin, outputName);
	fileName = (fileName == "" || fileName.size() > PATH_MAX ? "03_OSLabs_subprogram" : fileName);
	outputName = (outputName == "" || outputName.size() > PATH_MAX ? "Output.txt" : outputName);

	cout << "Input \"num1 num2 ...<endline>\" as command" << endl;

	int fdMutex = openShmFile(fileMutexName.c_str());
	setFileSize(fdMutex, sizeof(pthread_mutex_t) + sizeof(pthread_cond_t));

	pthread_mutex_t * mutex = (pthread_mutex_t *)openMMap(fdMutex, sizeof(pthread_mutex_t) + sizeof(pthread_cond_t));
	pthread_cond_t * cond = (pthread_cond_t *)(mutex + sizeof(pthread_mutex_t));

	pthread_mutexattr_t mutexattr;
	pthread_condattr_t condattr;

	if (pthread_mutexattr_setpshared(&mutexattr, PTHREAD_PROCESS_SHARED)) {
		throw invalid_argument("Mutexattr set failed");
	}
	if (pthread_mutex_init(mutex, &mutexattr)) {
		throw invalid_argument("Mutex init failed");
	}

	if (pthread_condattr_setpshared(&condattr, PTHREAD_PROCESS_SHARED)) {
		throw invalid_argument("Condattr set failed");
	}
	if (pthread_cond_init(cond, &condattr)) {
		throw invalid_argument("Cond init failed");
	}

	int fdData = openShmFile(fileDataName.c_str());
	setFileSize(fdData, (MAX_LEN + 1) * sizeof(int)); // 1 addition place for nums count
	int * data = (int *)openMMap(fdData, (MAX_LEN + 1) * sizeof(int));

	data[0] = 0; // for a while there 0 items

	int pid = fork();

	if (pid < 0) {
		cerr << "Error MP: fork creating failed" << endl;
	}
	else if (pid == 0) { // Child process
		char * argv[] = { (char *)fileName.c_str()
						, (char *)outputName.c_str()
						, (char *)fileMutexName.c_str()
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

			if (not getline(cin, command)) {
				data[0] = EOF;
				pthread_cond_signal(cond);
				pthread_mutex_unlock(mutex);
				break;
			}

			int ints[MAX_LEN]{ 0 };
			int i = 0, num;

			stringstream ss(command, ios_base::in);
			while (ss >> num) {
				if (i >= MAX_LEN) {
					stringstream errorstream;
					errorstream << "Error: string must have " << MAX_LEN << " numbers max" << endl;
					throw runtime_error(errorstream.str());
				}
				ints[i++] = num;
			}

			data[0] = i;// set nums count
			memcpy(&data[1], ints, MAX_LEN);

			pthread_cond_signal(cond);
			pthread_mutex_unlock(mutex);
		}

		wait(NULL);

		pthread_mutex_destroy(mutex);
		pthread_cond_destroy(cond);
		pthread_mutexattr_destroy(&mutexattr);
		pthread_condattr_destroy(&condattr);
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
