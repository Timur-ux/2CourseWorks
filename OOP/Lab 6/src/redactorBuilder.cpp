#include "redactorBuilder.hpp"
#include <fstream>


std::shared_ptr<LocationRedactor> RedactorDirector::createDangeonRedactor(Builder & builder) {
	auto outFile = std::make_shared<std::ofstream>(fileLogName);

	auto redactorLog = std::make_shared<RedactorLogObserver>(outFile);

	auto locationLog = std::make_shared<LocationLogObserver>(outFile);
	auto location = std::make_shared<DangeonLocation>(locationLog);

	auto battleManager = std::make_shared<BattleManager>(location);

	auto serializer = std::make_shared<LocationSerializer>(location);

	auto undoLog = std::make_shared<UndoManagerLogObserver>(outFile);
	auto undo = std::make_shared<DangeonUndoManager>(location, undoLog);

	builder.setLocation(location)
		.setBattleManager(battleManager)
		.setObserver(redactorLog)
		.setSerializer(serializer)
		.setUndoManager(undo);

	return builder.build();
}

Builder::Builder() {
	redactor = std::make_shared<LocationRedactor>();
}

std::shared_ptr<LocationRedactor> Builder::build() {
	return redactor;
}

Builder & Builder::setObserver(std::shared_ptr<LogObserver> _observer) {
	redactor->setObserver(_observer);

	return *this;
}

Builder & Builder::setLocation(std::shared_ptr<ILocation> _location) {
	redactor->setLocation(_location);
}

Builder & Builder::setBattleManager(std::shared_ptr<BattleManager> _battleManager) {
	redactor->setBattleManager(_battleManager);

	return *this;
}

Builder & Builder::setSerializer(std::shared_ptr<LocationSerializer> _serializer) {
	redactor->setSerializer(_serializer);

	return *this;
}

Builder & Builder::setUndoManager(std::shared_ptr<DangeonUndoManager> _undoManager) {
	redactor->setUndoManager(_undoManager);
}
