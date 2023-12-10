#include "generators/idGenerator.hpp"

long long IdGenerator::getId() {
    if (not returnedIDs.empty()) {
        long long result = returnedIDs.top();
        returnedIDs.pop();
        return result;
    }

    return currentHigherId++;
}

void IdGenerator::freeId(long long id) {
    if (id < currentHigherId) {
        returnedIDs.push(id);
    }
}
