#include "Observer.hpp"

LogObserver & LogObserver::setPrefix(std::string _prefix) {
	prefix = "[" + _prefix + "]";

	return *this;
}

void LogObserver::update(std::shared_ptr<IUpdateData> data) {
	std::string dataStr = data->asString();
	*outStream << prefix << " " << dataStr << std::endl;
}

void Observer::setOutputStream(std::shared_ptr<std::ostream> other) {
	outStream = other;
}
