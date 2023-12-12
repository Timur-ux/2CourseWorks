#include <gtest/gtest.h>
#include <memory>
#include <chrono>

#include "mob/allMobsHeadersInOneHeader.hpp"
#include "Location.hpp"

using namespace std::chrono_literals;

TEST(mobTest, moveTest) {
    std::shared_ptr<ILocation> location = std::make_shared<DangeonLocation>();
    auto mob = MobFabric::create<Elf>("Unnamed");
    double dx = ElfMoveRange;
    Position expected(dx, 0);
    Position given;

    location->addMob(MobData(mob, Position(0, 0), enumMobType::Elf));
    mob->moveWithShift(dx, 0, 1000ms);

    MobData & mobData = location->getMobDataBy(mob->getId());
    given = mobData.getPosition();

    EXPECT_EQ(given, expected);
}