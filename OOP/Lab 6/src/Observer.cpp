#include "Observer.hpp"

LogObserver & LogObserver::setPrefix(std::string _prefix) {
	prefix = "[" + _prefix + "]";
}

void LogObserver::update(IUpdateData & data) {
	*outStream << prefix << " " << data.asString() << std::endl;
}

void Observer::setOutputStream(std::shared_ptr<std::ostream> other) {
	outStream = other;
}

std::string LocationUpdateData::asString() {
	return data;
}

void LocationUpdateData::setData(std::string _data) {
	data = _data;
}

LocationLogObserver & LocationLogObserver::onAdd(const MobData & data, const Position & newPos) {
	LocationUpdateData data;

}
