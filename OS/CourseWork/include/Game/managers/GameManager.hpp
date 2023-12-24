#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include "Messages/MessageObserver.hpp"
#include "Messages/MessageVisitor.hpp"
#include "Network/interfaces/IServer.hpp"
#include "Messages/concretMessages/allConcretMessages.hpp"
#include "Game/messages/concretMessages/allConcretMessages.hpp"
#include "Game/player/Player.hpp"
#include "safeBool.hpp"

#include <map>
#include <string>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

namespace game {
	class GameManager
		: public ::message::ISubscriber
		, public ::message::IMessageVisitor {
	private:
		network::IServer& server;
		std::map<long long, Player> clients;
		SafeBool isNowGameRunning{ false };

		void provideGame();
	public:
		GameManager(network::IServer& _server) : server(_server) {}

		void subscribeTo(::message::IObserver*) override;
		void notify(::message::IMessage&) override;

		void visit(message::request::IStartGame&) override;
		void visit(message::request::IDisconnect&) override;

		void visit(message::reply::ISelectWord&) override;
		void visit(message::reply::IGuessWord&) override;
	};
}

#endif