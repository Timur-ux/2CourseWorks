#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include "Messages/MessageObserver.hpp"
#include "../visitors/MessageVisitor.hpp"
#include "Network/interfaces/IServer.hpp"
#include "Game/player/Player.hpp"

#include <map>
#include <string>

namespace game {
	class GameManager
		: public ::message::ISubscriber
		, public message::request::IGameMessageVisitor
		, public message::reply::IGameMessageVisitor {
	private:
		network::IServer& server;
		std::map<long long, Player> clients;
	public:
		GameManager(network::IServer& _server) : server(_server) {}

		void subscribeTo(::message::IObserver*) override;
		void notify(::message::IMessage) override;

		void visit(message::request::IStartGame&) override;
		void visit(message::request::ISelectWord&) override;
		void visit(message::request::IGuessWord&) override;
		void visit(message::request::IDisconnect&) override;

		void visit(message::reply::ISelectWord&) override;
		void visit(message::reply::IGuessWord&) override;
	};
}

#endif