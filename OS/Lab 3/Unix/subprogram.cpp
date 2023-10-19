#include <iostream>
#include <unistd.h>
#include <string>
#include <sstream>
#include <fstream>

#include <pthread.h>
#include <sys/mman.h>

#define MAX_LEN 100

using namespace std;

void * openMMap(int __fd, unsigned long int size);

int main(int argc, char * argv[]) {

	if (argc < 4) {
		stringstream errorstream;
		errorstream << "Usage: " << argv[0] << " <outputFileName> <fileConddeskriptor> <fileDataDeskriptor>";
		throw invalid_argument(errorstream.str());
	}

	ofstream outputStream(argv[1]);


	int mutexPos = sizeof(pthread_cond_t);
	int statePos = mutexPos + sizeof(pthread_mutex_t);

	int fileCondFd = atoi(argv[2]);
	int fileDataFd = atoi(argv[3]);
	void * mmapCond = openMMap(fileCondFd, sizeof(pthread_cond_t) + sizeof(pthread_mutex_t) + sizeof(bool));
	void * mmapData = openMMap(fileDataFd, (MAX_LEN + 1) * sizeof(int));

	int * data = static_cast<int *>(mmapData);

	while (true) {
		pthread_cond_wait(
			static_cast<pthread_cond_t *>(mmapCond),
			static_cast<pthread_mutex_t *>(mmapCond + mutexPos)
		);

		if (*static_cast<bool *>(mmapCond + statePos) == false) {
			break;
		}

		if (data[0] == '\0') {
			continue;
		}
		int result = 0;
		for (int i = 0; i < MAX_LEN; ++i) {
			result += data[i];
		}

		outputStream << result << endl;
	}
	outputStream.close();
}

void * openMMap(int __fd, unsigned long int size) {
	void * result;
	if ((result = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, __fd, 0)) == MAP_FAILED) {
		stringstream errorstream;
		errorstream << "Can't create mmap to deskriptor " << __fd << " with size " << size;
		throw runtime_error(errorstream.str());
	}

	return result;
}
