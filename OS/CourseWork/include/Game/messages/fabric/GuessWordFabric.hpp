#ifndef GUESS_WORD_FABRIC_H_
#define GUESS_WORD_FABRIC_H_

#include "Messages/messageFabric/ConcretFabric/IMessageFabric.hpp"
#include "../concretMessages/interfaces/IGuessWord.hpp"

namespace game {
	namespace message {
		namespace fabric {
			namespace request {
				class GuessWord : public ::message::fabric::IMessageFabric {
				private:
					std::shared_ptr<message::request::IGuessWord> message;
				public:
					GuessWord(pt::ptree data) {
						configureFromRaw(data);
					}

					GuessWord();

					IMessageFabric& configureFromRaw(pt::ptree) override;
					std::shared_ptr<::message::IMessage> getMessage() override {
						return message;
					}
				};
			} // !game::message::fabric::request

			namespace reply {
				class GuessWord : public ::message::fabric::IMessageFabric {
				private:
					std::shared_ptr<message::reply::IGuessWord> message;
				public:
					GuessWord(pt::ptree data) {
						configureFromRaw(data);
					}

					GuessWord(long long id, std::string login, std::string word, std::string opponent);

					IMessageFabric& configureFromRaw(pt::ptree) override;
					std::shared_ptr<::message::IMessage> getMessage() override {
						return message;
					}
				};
			} // !game::message::fabric::reply
		} // !game::message::fabric
	} // !game::message
} // !game

#endif // !GUESS_WORD_FABRIC_H_