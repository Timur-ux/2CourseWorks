#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

class IUpdateData;

class Observer {
protected:
    std::shared_ptr<std::ostream> outStream;
public:
    Observer(std::shared_ptr<std::ostream> _outStream) : outStream(_outStream) {}

    virtual void update(std::shared_ptr<IUpdateData> data) = 0;
    virtual void setOutputStream(std::shared_ptr<std::ostream> other);
};

class LogObserver : public Observer {
protected:
    std::string prefix = "[Undefined Log]";
public:
    LogObserver() = delete;
    LogObserver(std::shared_ptr<std::ofstream> _outStream) : Observer(_outStream) {};

    virtual LogObserver & setPrefix(std::string _prefix);

    void update(std::shared_ptr<IUpdateData> data) override;
};

class RedactorLogObserver : public LogObserver {
public:
    RedactorLogObserver(std::shared_ptr<std::ofstream> _outStream) : LogObserver(_outStream) {
        prefix = "[Redactor]";
    }
};

class UndoManagerLogObserver : public LogObserver {
public:
    UndoManagerLogObserver(std::shared_ptr<std::ofstream> _outStream) : LogObserver(_outStream) {
        prefix = "[Undo Manager]";
    }
};

class MobData;
struct Position;
class LocationLogObserver : public LogObserver {
public:
    LocationLogObserver(std::shared_ptr<std::ofstream> _outStream) : LogObserver(_outStream) {
        prefix = "[Location]";
    }

    LocationLogObserver & onAdd(const MobData & mobData);
    LocationLogObserver & onMove(const MobData & mobData, const Position & oldPos, const Position & newPos);
    LocationLogObserver & onRemove(const MobData & mobData);
};

class IUpdateData {
public:
    virtual std::string asString() = 0;
};

class LocationUpdateData : public IUpdateData {
private:
    std::shared_ptr<const MobData> mobData;
    std::string action = "";
    std::string additionalArgs = "";
public:
    friend LocationLogObserver;
    LocationUpdateData(std::shared_ptr<const MobData> _mobData) : mobData(_mobData) {}

    std::string asString() override;
};


struct ILocationSubscriber;
struct IMobObserver {
    virtual void on_move(ILocationSubscriber * subscriber, double dx, double dy) = 0;
};

struct ILocationSubscriber {
    virtual void setMobObserver(IMobObserver * observer) = 0;

    virtual long long getId() = 0;
    virtual void on_move(double eta) = 0;
};
#endif // OBSERVER_H_