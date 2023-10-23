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

int openShmFile(const char * fileName);
void * openMMap(int __fd, unsigned long int size);

int main(int argc, char * argv[]) {
	if (argc != 4) {
		stringstream errorstream;
		errorstream << "Usage: " << argv[0] << " <outputFileName> <fileMutexName> <fileDataName>";
		throw invalid_argument(errorstream.str());
	}

	ofstream outputStream(argv[1]);

	int fdMutex = openShmFile(argv[2]);
	int fdData = openShmFile(argv[3]);

	pthread_mutex_t * mutex = (pthread_mutex_t *)openMMap(fdMutex, sizeof(pthread_mutex_t) + sizeof(pthread_cond_t));
	pthread_cond_t * cond = (pthread_cond_t *)(mutex + sizeof(pthread_mutex_t));

	int * data = (int *)openMMap(fdData, (MAX_LEN + 1) * sizeof(int));


	while (true) {
		pthread_mutex_lock(mutex);
		while (data[0] == 0)
			pthread_cond_wait(cond, mutex);

		if (data[0] == EOF) {
			pthread_mutex_unlock(mutex);
			break;
		}

		int result = 0;
		for (int i = 1; i < data[0] + 1; ++i) {
			result += data[i];
		}
		outputStream << result << endl;

		data[0] = 0;
		pthread_mutex_unlock(mutex);
	}

	outputStream.close();
}

int openShmFile(const char * fileName) {
	int file = shm_open(fileName, O_RDWR | O_EXCL, 0777);
	if (file == -1) {
		stringstream errorstream;
		errorstream << "Can't open " << fileName << " with " << 0777 << " mode, errno = " << errno;
		throw runtime_error(errorstream.str());
	}

	return file;
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