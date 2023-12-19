#ifndef MESSAGE_MANAGER_H_
#define MESSAGE_MANAGER_H_

#include <boost/property_tree/ptree.hpp>
#include <map>
#include "GameManager.hpp"

namespace pt = boost::property_tree;

class IMessageManager {
public:
	virtual void push(pt::ptree message) = 0;
};

class GamesMessageManager : public IMessageManager {
private:
	std::map<long long, GameManager&> games;
	MessageQueue<pt::ptree> serverMQ;
public:
	void push(pt::ptree data) override;

	MessageQueue<pt::ptree>& getServerMQ();
};

#endif // !MESSAGE_MANAGER_H_
