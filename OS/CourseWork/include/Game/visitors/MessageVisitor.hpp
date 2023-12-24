#ifndef GAME_MESSAGE_VISITOR_H_
#define GAME_MESSAGE_VISITOR_H_

namespace message {
	class DataMessage;
}

namespace game {
	namespace message {
	namespace request {
		class IStartGame;
		class ISelectWord;
		class IGuessWord;
		class IDisconnect;

		class IGameMessageVisitor {
		public:
			virtual void visit(IStartGame&) {};
			virtual void visit(ISelectWord&) {};
			virtual void visit(IGuessWord&) {};
			virtual void visit(IDisconnect&) {};
			virtual void visit(::message::DataMessage&) {}
		};
		} // !game::message::request

		namespace reply {
			class ISelectWord;
			class IGuessWord;

			class IGameMessageVisitor {
			public:
				virtual void visit(ISelectWord&) {};
				virtual void visit(IGuessWord&) {};
			};
		} // !game::message::reply
	} // !game::message
}

#endif // !I_GAME_VISITOR_H_
