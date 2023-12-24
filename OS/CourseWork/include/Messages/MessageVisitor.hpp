#ifndef MESSAGE_VISITOR_H_
#define MESSAGE_VISITOR_H_

namespace game {
	namespace message {
		namespace request {
			class IStartGame;
			class ISelectWord;
			class IGuessWord;
			class IDisconnect;
		}

		namespace reply {
			class ISelectWord;
			class IGuessWord;
		}
	}
}

namespace message {
	class DataMessage;
	namespace request {
		class IAuth;
		class IPing;
		class IGetLogins;
		class ICreateNewGame;
	} // !request

	namespace reply {
		class IAuth;
		class IPing;
		class IGetLogins;
		class IInviteToGame;
	} // !reply

	class IMessageVisitor {
	public:
		virtual void visit(DataMessage&) {}

		virtual void visit(request::IAuth& message) {};
		virtual void visit(request::IPing& message) {};
		virtual void visit(request::IGetLogins& message) {};
		virtual void visit(request::ICreateNewGame& message) {};

		virtual void visit(reply::IAuth& message) {};
		virtual void visit(reply::IPing& message) {};
		virtual void visit(reply::IGetLogins& message) {};
		virtual void visit(reply::IInviteToGame& message) {};

		virtual void visit(game::message::request::IStartGame&) {};
		virtual void visit(game::message::request::ISelectWord&) {};
		virtual void visit(game::message::request::IGuessWord&) {};
		virtual void visit(game::message::request::IDisconnect&) {};

		virtual void visit(game::message::reply::ISelectWord&) {};
		virtual void visit(game::message::reply::IGuessWord&) {};
	};
}
#endif // ! MESSAGE_VISITOR_H_