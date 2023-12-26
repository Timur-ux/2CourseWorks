#ifndef I_MESSAGE_FABRIC_H_
#define I_MESSAGE_FABRIC_H_

#include "Messages/Message.hpp"

#include <boost/property_tree/ptree.hpp>
#include <string>

namespace pt = boost::property_tree;

namespace message {
	namespace fabric {
		class IMessageFabric {
		public:
			virtual IMessageFabric & configureFromRaw(pt::ptree) = 0;
			virtual std::shared_ptr<IMessage> getMessage() = 0;
		};
	}
} // !message

#endif // !I_MESSAGE_FABRIC_H_
