#ifndef GUESS_WORD_FABRIC_H_
#define GUESS_WORD_FABRIC_H_

#include "Messages/messageFabric/ConcretFabric/IMessageFabric.hpp"
#include "../concretMessages/interfaces/IGuessWord.hpp"

namespace game {
	namespace message {
		namespace fabric {
			namespace request {
				class GuessWord : public ::message::fabric::request::IMessageFabric {
				public:
					GuessWord() = default;

					std::shared_ptr<::message::IMessage> getMessage() override;
				};
			} // !game::message::fabric::request

			namespace reply {
				class GuessWord : public ::message::fabric::reply::IMessageFabric {
				public:
					GuessWord(long long id, std::string login, std::string word, std::string opponent);

					std::shared_ptr<::message::IMessage>
						getMessage() override;
				};
			} // !game::message::fabric::reply
		} // !game::message::fabric
	} // !game::message
} // !game

#endif // !GUESS_WORD_FABRIC_H_