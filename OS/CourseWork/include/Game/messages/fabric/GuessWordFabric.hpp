#ifndef GUESS_WORD_FABRIC_H_
#define GUESS_WORD_FABRIC_H_

#include "Messages/messageFabric/ConcretFabric/IMessageFabric.hpp"
#include "../concretMessages/interfaces/IGuessWord.hpp"

namespace game {
	namespace message {
		namespace fabric {
			namespace request {
				class GuessWord : public ::message::fabric::IMessageFabric {
				public:
					GuessWord() = default;

					IMessageFabric& configureFromRaw(pt::ptree) override;
					std::shared_ptr<::message::IMessage> getMessage() override;
				};
			} // !game::message::fabric::request

			namespace reply {
				class GuessWord : public ::message::fabric::IMessageFabric {
				public:
					GuessWord(pt::ptree data) {
						configureFromRaw(data);
					}

					GuessWord(long long id, std::string login, std::string opponent, std::string word);

					IMessageFabric& configureFromRaw(pt::ptree) override;
					std::shared_ptr<::message::IMessage> getMessage() override;
				};
			} // !game::message::fabric::reply
		} // !game::message::fabric
	} // !game::message
} // !game

#endif // !GUESS_WORD_FABRIC_H_