#include "MessageManager.hpp"
#include "print.hpp"

void GamesMessageManager::push(pt::ptree data)
{
	boost::optional<long long> id = data.get_optional<long long>("Game.id");
	if (id) {
		auto gameIt = games.find(id.value());
		if (gameIt == std::end(games)) {
			printErr() << "Game message manager: undefined game's id" << std::endl;
		}

		gameIt->second.pushMessage(data);
	}
	else {
		serverMQ.push(data);
	}
}

MessageQueue<pt::ptree>& GamesMessageManager::getServerMQ()
{
	return serverMQ;
}
