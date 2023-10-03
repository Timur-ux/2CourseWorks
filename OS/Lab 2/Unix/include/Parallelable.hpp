
using namespace std;

struct WorkerData;

class Parallelable {
public:
    virtual WorkerData * getWorkerData(void *) = 0;
};