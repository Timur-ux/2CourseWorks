#ifndef SELECT_WORD_FABRIC_H_
#define SELECT_WORD_FABRIC_H_

#include "Messages/messageFabric/ConcretFabric/IMessageFabric.hpp"

namespace game {
	namespace message {
		namespace fabric {
			namespace request {
				class SelectWord : public ::message::fabric::request::IMessageFabric {
				public:
					SelectWord() = default;

					::message::IMessage getMessage() override;
				};
			} // !game::message::fabric::request

			namespace reply {
				class SelectWord : public ::message::fabric::reply::IMessageFabric {
				public:
					SelectWord(std::string login, std::string word);

					::message::IMessage getMessage() override;
				};
			} // !game::message::fabric::reply
		} // !game::message::fabric
	} // !game::message
} // !game

#endif // !SELECT_WORD_FABRIC_H_