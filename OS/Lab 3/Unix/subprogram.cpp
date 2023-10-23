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
	if (argc != 3) {
		stringstream errorstream;
		errorstream << "Usage: " << argv[0] << " <outputFileName> <fileDataName>";
		throw invalid_argument(errorstream.str());
	}

	ofstream outputStream(argv[1]);

	int fdData = shm_open(argv[2], O_RDWR, 0777);

	void * mmapData = openMMap(fdData, (MAX_LEN + 1) * sizeof(int));
	int * data = (int *)(mmapData);

	data[0] = -123456789;// -123456789 -- wait parent process

	while (true) {
		if (data[0] == -123456789) {
			continue;
		}
		if (data[0] == -111333666) {// -111333999 exit
			break;
		}

		int result = 0;
		for (int i = 0; i < MAX_LEN; ++i) {
			result += data[i];
		}

		outputStream << result << endl;

		data[0] = -123456789;
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