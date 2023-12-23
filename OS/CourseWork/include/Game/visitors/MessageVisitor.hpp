#ifndef GAME_MESSAGE_VISITOR_H_
#define GAME_MESSAGE_VISITOR_H_

namespace game {
	namespace message {
		namespace request {
			class IStartGame;
			class ISelectWord;
			class IGuessWord;
			class IDisconnect;

			class IGameMessageVisitor {
			public:
				virtual void visit(IStartGame&) = 0;
				virtual void visit(ISelectWord&) = 0;
				virtual void visit(IGuessWord&) = 0;
				virtual void visit(IDisconnect&) = 0;
			};
		} // !game::message::request

		namespace reply {
			class IStartGame;
			class ISelectWord;
			class IGuessWord;
			class IDisconnect;

			class IGameMessageVisitor {
			public:
				virtual void visit(IStartGame&) = 0;
				virtual void visit(ISelectWord&) = 0;
				virtual void visit(IGuessWord&) = 0;
				virtual void visit(IDisconnect&) = 0;
			};
		} // !game::message::reply
	} // !game::message
}

#endif // !I_GAME_VISITOR_H_
