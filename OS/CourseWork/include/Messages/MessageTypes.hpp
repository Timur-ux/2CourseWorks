#ifndef MESSAGE_TYPES_H_
#define MESSAGE_TYPES_H_

namespace message {
	enum class Type {
		auth
		, ping
		, getLogins
		, createNewGame
		, dataMessage
		, gameAction
	};
	
	enum class ReqRepType {
		request,
		reply
	};
}

#endif // ! MESSAGE_TYPES_H_