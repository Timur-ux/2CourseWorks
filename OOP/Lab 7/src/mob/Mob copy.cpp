#include "mob/Mob.hpp"
#include <cmath>
#include <cstdlib>

std::string Mob::getName() const {
    return name;
}

MobParameters::Status Mob::getStatus() const {
    std::shared_lock<std::shared_mutex> lock(mutex);
    return status;
}

void Mob::takeDamage(GameCube attackerCube) {
    GameCube ownCube;
    ownCube.throwCube();

    if (attackerCube.getValue() > ownCube.getValue()) {
        std::lock_guard<std::shared_mutex> lock(mutex);
        status = MobParameters::Status::died; // Health is 1. All die after any hit.
    }
}

double Mob::getAttackRange() const {
    return attackRange;
}

double Mob::getMoveRange() const {
    return moveRange;
}

void Mob::attack(Mob & other) const {
    GameCube ownCube;
    ownCube.throwCube();

    other.takeDamage(ownCube);
}



void Mob::moveWithShift(double dx, double dy, std::chrono::milliseconds dtime) {
    if (dx == 0 and dy == 0) {
        return;
    }

    double abs = sqrt(dx * dx + dy * dy);
    double ex = dx / abs, ey = dy / abs;

    double k = dtime.count() / 1000;

    double curMoveRange = moveRange * k;

    mobObserver->on_move(this, ex * curMoveRange, ey * curMoveRange);
}

long long Mob::getId() const {
    return id;
}

void Mob::setMobObserver(IMobObserver * other) {
    mobObserver = other;
}

std::ostream & operator<<(std::ostream & os, enumMobType type) {
    os << static_cast<int>(type);

    return os;
}

std::istream & operator>>(std::istream & is, enumMobType & type) {
    int intType;

    is >> intType;
    type = enumMobType{ intType };

    return is;
}

int throwCube() {
    return rand() % 6 + 1;
}
