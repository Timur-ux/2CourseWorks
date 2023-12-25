#ifndef DATA_MESSAGE_H_
#define DATA_MESSAGE_H_

#include "../Message.hpp"

#include <string>

namespace message {
	class DataMessage : public IMessage {
		std::string data;
	public:
		DataMessage(std::string _data) : data(_data) {}

		pt::ptree getData() override;

		void accept(::message::IMessageVisitor& visitor) {
			visitor.visit(*this);
		}
	};
}

#endif // !DATA_MESSAGE_H_
