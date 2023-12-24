#ifndef GAME_MESSAGE_TYPES_H_
#define GAME_MESSAGE_TYPES_H_

namespace game {
	namespace message {
		enum class Type {
			startGame
			, selectWord
			, guessWord
			, disconnect
		};
	} // !game::message
}

#endif // !GAME_MESSAGE_TYPES_H_
