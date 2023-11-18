#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <string>
#include <fstream>

struct IUpdateData {
	virtual void asString() = 0;
};

class IObserver {
public:
	virtual void update(IUpdateData & data) = 0;
};

class LogObserver : IObserver {
private:
	std::ofstream outputFStream;

	std::string prefix = "";
	std::string suffix = "";
public:
	LogObserver() = delete;
	LogObserver(std::string _outputFileName = "LogObserver", std::string _prefix = "")
		: outputFStream(_outputFileName)
		, prefix(_prefix) {
	}

	void setPrefix(std::string _prefix) {
		prefix = _prefix;
	}

	void setSuffix(std::string _suffix) {
		suffix = _suffix;
	}

	void update(IUpdateData & data) override;
};

#endif // OBSERVER_H_