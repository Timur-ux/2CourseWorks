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

class MobData;
struct Position;
class LocationLogObserver : public LogObserver {
public:
	LocationLogObserver(std::shared_ptr<std::ofstream> _outStream) : LogObserver(_outStream) {
		prefix = "[Location]";
	}

	LocationLogObserver & onAdd(const MobData & data, const Position & newPos);
	LocationLogObserver & onMove(const MobData & data, const Position & newPos);
	LocationLogObserver & onRemove(const MobData & data, const Position & newPos);
};

class IUpdateData {
public:
	virtual std::string asString() = 0;
};

class LocationUpdateData : public IUpdateData {
private:
	std::string data = "Location Update Data Unsetted";
public:
	LocationUpdateData() = default;
	LocationUpdateData(std::string _data) : data(_data) {}

	std::string asString() override;
	void setData(std::string _data);
};

#endif // OBSERVER_H_