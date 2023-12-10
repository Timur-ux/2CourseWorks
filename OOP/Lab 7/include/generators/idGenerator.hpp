#ifndef ID_GENERATOR_H_
#define ID_GENERATOR_H_

#include <queue>

class IdGenerator {
private:
    std::priority_queue<long long, std::vector<long long>, std::greater<long long>> returnedIDs;
    long long currentHigherId = 1;
public:
    long long getId();
    void freeId(long long id);
};

#endif