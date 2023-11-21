#include "Observer.hpp"

LogObserver & LogObserver::setPrefix(std::string _prefix) {
	prefix = "[" + _prefix + "]";
}

void LogObserver::update(std::shared_ptr<IUpdateData> data) {
	*outStream << prefix << " " << data->asString() << std::endl;
}

void Observer::setOutputStream(std::shared_ptr<std::ostream> other) {
	outStream = other;
}
