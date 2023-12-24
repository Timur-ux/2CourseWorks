#include "Game/managers/GameManager.hpp"

using namespace game;

void GameManager::notify(::message::IMessage message) {
	message.accept(*static_cast<message::request::IGameMessageVisitor*>(this));
	message.accept(*static_cast<message::reply::IGameMessageVisitor*>(this));
}
