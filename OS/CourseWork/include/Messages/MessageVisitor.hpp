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
			virtual void visit(IAuth& message) = 0;
			virtual void visit(IPing& message) = 0;
			virtual void visit(IGetLogins& message) = 0;
			virtual void visit(ICreateNewGame& message) = 0;
		};
	} // !request

	namespace reply {
		class IAuth;
		class IPing;
		class IGetLogins;
		class IInviteToGame;


		class IMessageVisitor {
		public:
			virtual void visit(IAuth& message) = 0;
			virtual void visit(IPing& message) = 0;
			virtual void visit(IGetLogins& message) = 0;
			virtual void visit(IInviteToGame& message) = 0;
		};
	} // !reply

}
#endif // ! MESSAGE_VISITOR_H_