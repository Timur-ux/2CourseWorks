#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <string>
#include <iostream>

struct IUpdateData {
	virtual void asString() = 0;
};

class Observer {
protected:
	static std::ostream output;
public:
	virtual void update(IUpdateData & data) = 0;
};

class LogObserver : Observer {
	std::string prefix = "";
	std::string suffix = "";
public:
	LogObserver() = delete;
	LogObserver(std::string _outputFileName = "LogObserver", std::string _prefix = "");

	void setPrefix(std::string _prefix);

	void setSuffix(std::string _suffix = ".log");

	void update(IUpdateData & data) override;
};

#endif // OBSERVER_H_