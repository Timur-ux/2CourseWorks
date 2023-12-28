#ifndef DATA_MESSAGE_H_
#define DATA_MESSAGE_H_

#include "../Message.hpp"

#include <string>

namespace message {
	class DataMessage : public IMessage {
	private:
		std::string messageData;
	public:
		DataMessage(std::string _data) : messageData(_data) {}

		pt::ptree getData() override;

		void accept(IMessageVisitor& visitor) override {
			visitor.visit(*this);
		}
	};
}

#endif // !DATA_MESSAGE_H_
