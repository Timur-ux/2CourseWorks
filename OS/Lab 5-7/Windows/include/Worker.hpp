#ifndef WORKER_H_
#define WORKER_H_
#include <string>
#include <map>

struct Data {
	std::string name;
	int value;

	Data() = default;
	Data(std::string _name, int _value) : name(_name), value(_value) {}
};

class Worker {
private:
	std::map<std::string, int> storage;
private:
	void set(Data data);
	int get(std::string name);
};

enum class RequestType {
	setValue,
	getValue,
	stateCheck
};

#endif // !WORKER_H_
