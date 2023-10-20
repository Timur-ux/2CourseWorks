#include <iostream>
#include <unistd.h>
#include <string>
#include <sstream>
#include <fstream>

#include <pthread.h>
#include <sys/mman.h>
#include <fcntl.h>

#define MAX_LEN 100

using namespace std;

void * openMMap(int __fd, unsigned long int size);

int main(int argc, char * argv[]) {
	if (argc != 4) {
		stringstream errorstream;
		errorstream << "Usage: " << argv[0] << " <outputFileName> <fileCondDeskriptor> <fileDataDeskriptor>";
		throw invalid_argument(errorstream.str());
	}

	ofstream outputStream(argv[1]);

	int mutexPos = sizeof(pthread_cond_t);
	int statePos = mutexPos + sizeof(pthread_mutex_t);

	int fdCond = shm_open(argv[2], O_CREAT | O_RDWR, 0777);
	int fdData = shm_open(argv[3], O_CREAT | O_RDWR, 0777);

	void * mmapCond = openMMap(fdCond
							 , sizeof(pthread_cond_t) + sizeof(pthread_mutex_t) + sizeof(bool)
	);

	pthread_cond_t * cond = (pthread_cond_t *)mmapCond;
	pthread_mutex_t * mutex = (pthread_mutex_t *)(mmapCond + mutexPos);
	bool * state = (bool *)(mmapCond + statePos);

	void * mmapData = openMMap(fdData, (MAX_LEN + 1) * sizeof(int));

	int * data = (int *)(mmapData);
	while (true) {
		cout << "CHild 0" << endl;
		pthread_mutex_lock(mutex);
		cout << "CHILD" << endl;
		pthread_cond_wait(cond, mutex);

		if (*state == false) {
			pthread_mutex_unlock(mutex);
			break;
		}

		for (int i = 0; i < MAX_LEN; ++i) {
			cout << data[i] << endl;
		}
		cout << endl;

		int result = 0;
		for (int i = 0; i < MAX_LEN; ++i) {
			result += data[i];
		}

		cout << result << endl;
		outputStream << result << endl;
		pthread_mutex_unlock(mutex);
	}
	outputStream.close();
}

void * openMMap(int __fd, unsigned long int size) {
	void * result = mmap(NULL, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED, __fd, 0);
	if (result == MAP_FAILED) {
		stringstream errorstream;
		errorstream << "Can't create mmap to deskriptor " << __fd << " with size " << size << ", errno = " << errno;
		throw runtime_error(errorstream.str());
	}

	return result;
}
