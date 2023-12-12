#include "Location.hpp"

#include <vector>
#include <cmath>

std::istream & operator>>(std::istream & is, Position & pos) {
    is >> pos.x >> pos.y;

    return is;
}

std::ostream & operator<<(std::ostream & os, const Position & pos) {
    os << pos.getX() << " " << pos.getY();

    return os;
}

std::ostream & operator<<(std::ostream & os, const Position && pos) {
    os << (const Position &)pos;

    return os;
}

bool operator==(const Position & lhs, const Position & rhs) {
    return (lhs.getX() == rhs.getX()) and (lhs.getY() == rhs.getY());
}

std::ostream & operator<<(std::ostream & os, const MobData & _mobData) {
    os << "Id: " << _mobData.getId() << std::endl
        << "type: " << MobTypeCvt::to_string(_mobData.getMobType()) << std::endl
        << "name: " << replace(_mobData.getMob()->getName(), ' ', '_') << std::endl
        << "position: " << _mobData.getPosition() << std::endl;

    return os;
}

std::istream & operator>>(std::istream & is, MobData & _mobData) {
    std::string temp, type, name;
    int id;
    Position pos;

    if (not(is >> temp)) {
        return is;
    }

    is >> id >> temp >> type >> temp >> name >> temp >> pos;
    name = replace(name, '_', ' ');

    _mobData.mob = MobFabric::create(type, name);
    _mobData.type = MobTypeCvt::to_enum(type);
    _mobData.position = pos;

    return is;
}

void MobData::moveTo(Position newPos) {
    std::lock_guard<std::shared_mutex> lock(mutex);

    position = newPos;
}

MobData & MobData::operator=(const MobData & other) {
    mob = other.mob;
    position = other.getPosition();
    type = other.getMobType();

    return *this;
}

long long MobData::getId() const {
    return mob->getId();
}

Position MobData::getPosition() const {
    std::shared_lock<std::shared_mutex> lock(mutex);
    return position;
}

enumMobType MobData::getMobType() const {
    return type;
}

std::shared_ptr<Mob> MobData::getMob() const {
    return mob;
}

double MobData::getAttackRange() const {
    return mob->getAttackRange();
}

double MobData::getMoveRange() const {
    return mob->getMoveRange();
}

MobParameters::Status MobData::getStatus() const {
    return mob->getStatus();
}

MobData & DangeonLocation::getMobDataBy(int id) {
    auto mobIt = mobs.find(id);
    if (mobIt == std::end(mobs)) {
        throw std::invalid_argument("Undefined mob id: " + std::to_string(id));
    }

    return mobIt->second;
}

std::string LocationUpdateData::asString() {
    std::stringstream dataStream;
    dataStream << "Id: " << mobData->getId() << "; action: " << action << "; " << additionalArgs;

    return dataStream.str();
}

LocationLogObserver & LocationLogObserver::onAdd(const MobData & mobData) {
    auto data = std::make_shared<LocationUpdateData>(
        std::make_shared<const MobData>(mobData)
    );

    std::stringstream argsStream;
    argsStream << "position: " << mobData.getPosition();

    data->action = "add";
    data->additionalArgs = argsStream.str();
    update(data);

    return *this;
}
LocationLogObserver & LocationLogObserver::onMove(const MobData & mobData, const Position & oldPos, const Position & newPos) {
    auto data = std::make_shared<LocationUpdateData>(
        std::make_shared<const MobData>(mobData)
    );

    std::stringstream argsStream;
    argsStream << "from " << oldPos << " to " << newPos;

    data->action = "move";
    data->additionalArgs = argsStream.str();

    update(data);
    return *this;
}

LocationLogObserver & LocationLogObserver::onRemove(const MobData & mobData) {
    auto data = std::make_shared<LocationUpdateData>(
            std::make_shared<const MobData>(mobData)
    );
    data->action = "remove";
    update(data);

    return *this;
}

const std::map<int, MobData> & DangeonLocation::getMobsData() {
    return mobs;
}

DangeonLocation & DangeonLocation::setLogObserver(std::shared_ptr<LocationLogObserver> _logObserver) {
    logObserver = _logObserver;

    return *this;
}

DangeonLocation & DangeonLocation::setUndoManager(std::shared_ptr<DangeonUndoManager> _undoManager) {
    undoManager = _undoManager;

    return *this;
}

void DangeonLocation::on_move(ILocationSubscriber * subscriber, double dx, double dy) {
    int id = subscriber->getId();
    auto mobIt = mobs.find(id);
    if (mobIt == std::end(mobs)) {
        return;
    }

    auto & mobData = mobIt->second;

    Position mobPos = mobData.getPosition();
    Position newPos{ mathMod(mobPos.getX() + dx, width), mathMod(mobPos.getY() + dy, height) };

    mobData.position = newPos;
}

void DangeonLocation::drawMap() {
    std::vector<std::vector<char>> map(height, std::vector<char>(width, ' '));
    for (auto & pair : mobs) {
        auto & mobData = pair.second;
        Position pos = mobData.getPosition();
        char c;

        if (mobData.getStatus() == MobParameters::Status::died) {
            c = '.';
        }
        else {
            c = MobTypeCvt::to_string(mobData.getMobType())[0];
        }

        map[pos.getY()][pos.getX()] = c;
    }

    std::ostringstream outStream;

    outStream << std::endl;
    for (auto & row : map) {
        for (char c : row) {
            outStream << '[' << c << ']';
        }
        outStream << std::endl;
    }
    outStream << std::endl;

    print() << outStream.str();
}
