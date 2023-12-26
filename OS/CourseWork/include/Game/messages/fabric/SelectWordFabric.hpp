#ifndef SELECT_WORD_FABRIC_H_
#define SELECT_WORD_FABRIC_H_

#include "Messages/messageFabric/ConcretFabric/IMessageFabric.hpp"
#include "../concretMessages/interfaces/ISelectWord.hpp"

namespace game {
	namespace message {
		namespace fabric {
			namespace request {
				class SelectWord : public ::message::fabric::IMessageFabric {
				public:
					SelectWord() = default;

					IMessageFabric& configureFromRaw(pt::ptree) override;
					std::shared_ptr<::message::IMessage> getMessage() override;
				};
			} // !game::message::fabric::request

			namespace reply {
				class SelectWord : public ::message::fabric::IMessageFabric {
				public:
					SelectWord(pt::ptree data) {
						configureFromRaw(data);
					}

					SelectWord(long long id, std::string login, std::string word);

					IMessageFabric& configureFromRaw(pt::ptree) override;
					std::shared_ptr<::message::IMessage> getMessage() override;
				};
			} // !game::message::fabric::reply
		} // !game::message::fabric
	} // !game::message
} // !game

#endif // !SELECT_WORD_FABRIC_H_