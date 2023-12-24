#ifndef MESSAGE_VISITOR_H_
#define MESSAGE_VISITOR_H_

namespace message {
	namespace request {
		class IAuth;
		class IPing;
		class IGetLogins;
		class ICreateNewGame;


		class IMessageVisitor {
		public:
			virtual void visit(IAuth& message) {};
			virtual void visit(IPing& message) {};
			virtual void visit(IGetLogins& message) {};
			virtual void visit(ICreateNewGame& message) {};
		};
	} // !request

	namespace reply {
		class IAuth;
		class IPing;
		class IGetLogins;
		class IInviteToGame;


		class IMessageVisitor {
		public:
			virtual void visit(IAuth& message) {};
			virtual void visit(IPing& message) {};
			virtual void visit(IGetLogins& message) {};
			virtual void visit(IInviteToGame& message) {};
		};
	} // !reply

}
#endif // ! MESSAGE_VISITOR_H_