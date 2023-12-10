#ifndef LOCATION_H_
#define LOCATION_H_

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <type_traits>

#include "mob/allMobsHeadersInOneHeader.hpp"
#include "Observer.hpp"
#include "utils.hpp"

struct Position {
    double x;
    double y;

    Position() = default;
    Position(double _x, double _y) : x(_x), y(_y) {}

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    friend std::istream & operator>>(std::istream & is, Position & pos);
    friend std::ostream & operator<<(std::ostream & os, const Position & pos);
    friend std::ostream & operator<<(std::ostream & os, const Position && pos);
    friend bool operator==(const Position & lhs, const Position & rhs);

};


class DangeonLocation;
class BattleManager;
class MobData {
private:
    std::shared_ptr<Mob> mob;
    Position position;
    enumMobType type;
public:
    friend DangeonLocation;
    friend BattleManager;

    MobData() = default;
    MobData(std::shared_ptr<Mob> _mob, Position _position, enumMobType _type, int _id = -1)
        : mob(_mob), position(_position), type(_type) {}

    MobData(const MobData & other) :
        mob(other.mob)
        , position(other.position)
        , type(other.type) {}



    long long getId() const;
    Position getPosition() const;
    enumMobType getMobType() const;
    std::shared_ptr<const Mob> getMob() const;

    friend std::ostream & operator<<(std::ostream & os, const MobData & _mobData);
    friend std::istream & operator>>(std::istream & is, MobData & _mobData);
};

class ILocation {
public:
    virtual ILocation & addMob(MobData _mobData) = 0;
    virtual ILocation & moveMob(int id, Position newPos) = 0;
    virtual ILocation & removeMob(int id) = 0;
    virtual MobData & getMobDataBy(int id) = 0;
    virtual const std::map<int, MobData> & getMobsData() = 0;
};

class DangeonUndoManager;
class DangeonLocation : public ILocation, public IMobObserver {
private:
    double width = 50;
    double height = 50;
    std::map<int, MobData> mobs;
    std::shared_ptr<LocationLogObserver> logObserver;
    std::shared_ptr<DangeonUndoManager> undoManager;
public:
    DangeonLocation() = default;
    DangeonLocation(std::shared_ptr<LocationLogObserver> _logObserver, std::shared_ptr<DangeonUndoManager> _undoManager)
        : logObserver(_logObserver)
        , undoManager(_undoManager) {}

    ILocation & addMob(MobData _mobData) override;
    ILocation & moveMob(int id, Position newPos) override;
    ILocation & removeMob(int id) override;
    MobData & getMobDataBy(int id) override;
    const std::map<int, MobData> & getMobsData() override;

    DangeonLocation & setLogObserver(std::shared_ptr<LocationLogObserver> _logObserver);
    DangeonLocation & setUndoManager(std::shared_ptr<DangeonUndoManager> _undoManager);

    void on_move(ILocationSubscriber * subscriber, double dx, double dy) override;
};

#endif // LOCATION_H_