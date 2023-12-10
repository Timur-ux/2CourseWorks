#include "battle/BattleManager.hpp"

#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>

double calcDistance(const Position & from, const Position & to);
std::shared_ptr<IBattleVisitor> getBattleVisitor(enumMobType type);

bool throwGameCubesAndCheckIfKill();

void BattleManager::provideBattleRound(double attackDistance) {
    std::list<long long> killedMobs;
    deadlist.erase(std::begin(deadlist), std::end(deadlist));
    auto & mobsData = battleLocation->getMobsData();

    for (auto & attackerPair : mobsData) {
        for (auto & defenderPair : mobsData) {
            auto & attacker = attackerPair.second;
            auto & defender = defenderPair.second;

            if (std::find(std::begin(killedMobs), std::end(killedMobs), attacker.getId()) != std::end(killedMobs)) {
                continue;
            }

            if (attacker.getId() == defender.getId()) {
                continue;
            }

            auto attackerVisitor = getBattleVisitor(attacker.getMobType());
            if (calcDistance(attacker.getPosition(), defender.getPosition()) <= attackDistance
                and defender.mob->accept(*attackerVisitor)) {
                if (throwGameCubesAndCheckIfKill()) {
                    deadlist.push_back(BattleEvent(attacker, defender));
                }
            }
        }
    }
}

std::list<BattleEvent> & BattleManager::getDeadListForLastRound() {
    return deadlist;
}

void BattleManager::setBattleLocation(std::shared_ptr<ILocation> _location) {
    battleLocation = _location;
}

double calcDistance(const Position & from, const Position & to) {
    double dx = from.getX() - to.getX();
    double dy = from.getY() - to.getY();

    return sqrt(dx * dx + dy * dy);
}

std::shared_ptr<IBattleVisitor> getBattleVisitor(enumMobType type) {
    switch (type) {
    case enumMobType::KnightStranger:
        return std::make_shared<Visitor<KnightStranger>>();
    case enumMobType::Elf:
        return std::make_shared<Visitor<Elf>>();
    case enumMobType::Dragon:
        return std::make_shared<Visitor<Dragon>>();
    case enumMobType::BaseMob:
        throw std::invalid_argument("Can not create battle visitor for base class: Mob");
    }
}

bool throwGameCubesAndCheckIfKill() {
    static int cubeSides = 6;
    int attackerThrow = rand() % cubeSides + 1;
    int defenderThrow = rand() % cubeSides + 1;

    return attackerThrow > defenderThrow;
}