#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include "generators/idGenerator.hpp"

TEST(idGeneratorTests, getTest) {
    IdGenerator idGenerator;

    long long id1 = idGenerator.getId();
    long long id2 = idGenerator.getId();
    EXPECT_GE(id1, 1);
    EXPECT_NE(id1, id2);
}

TEST(idGeneratorTests, freeTest) {
    IdGenerator idGenerator;

    long long id1 = idGenerator.getId();
    long long id2 = idGenerator.getId();

    idGenerator.freeId(id1);
    long long id3 = idGenerator.getId();

    EXPECT_NE(id2, id3);
    EXPECT_EQ(id1, id3);
}

TEST(idGeneratorTests, freeOrderTest) {
    IdGenerator idGenerator;

    std::vector<long long> IDs;
    for (int i = 0; i < 10; ++i) {
        IDs.push_back(idGenerator.getId());
    }

    std::vector<long long> freeIDs;
    for (int i = 0; i < 5; ++i) {
        int pos = rand() % IDs.size();
        freeIDs.push_back(IDs.at(pos));
        idGenerator.freeId(IDs.at(pos));
    }

    long long minId = -1;
    for (auto & id : freeIDs) {
        if (minId == -1) {
            minId = id;
        }
        if (minId > id) {
            minId = id;
        }
    }

    long long id = idGenerator.getId();

    EXPECT_EQ(minId, id);
}