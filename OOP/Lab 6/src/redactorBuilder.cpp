#include "redactorBuilder.hpp"
#include <fstream>


std::shared_ptr<LocationRedactor> RedactorDirector::createDangeonRedactor(Builder & builder, std::shared_ptr<std::ofstream> outFile, bool createNew) {
	if (builder.isAllCompounentsSet() and not(createNew)) {
		return builder.build();
	}

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
	redactor = std::shared_ptr<LocationRedactor>(nullptr);
}

std::shared_ptr<LocationRedactor> Builder::build() {
	if (redactor.get() != nullptr) {
		auto result = redactor;
		redactor = std::shared_ptr<LocationRedactor>(nullptr);
		return result;
	}
	redactor = std::make_shared<LocationRedactor>();

	redactor->setLocation(location)
		.setBattleManager(battleManager)
		.setObserver(observer)
		.setSerializer(serializer)
		.setUndoManager(undoManager);

	auto result = redactor;
	redactor = std::shared_ptr<LocationRedactor>(nullptr);

	allCompounentsSet = true;
	return result;
}

Builder & Builder::setObserver(std::shared_ptr<LogObserver> _observer) {
	observer = _observer;

	return *this;
}

Builder & Builder::setLocation(std::shared_ptr<ILocation> _location) {
	location = _location;

	return *this;
}

Builder & Builder::setBattleManager(std::shared_ptr<BattleManager> _battleManager) {
	battleManager = _battleManager;

	return *this;
}

Builder & Builder::setSerializer(std::shared_ptr<LocationSerializer> _serializer) {
	serializer = _serializer;

	return *this;
}

Builder & Builder::setUndoManager(std::shared_ptr<DangeonUndoManager> _undoManager) {
	undoManager = _undoManager;

	return *this;
}

bool Builder::isAllCompounentsSet() {
	return allCompounentsSet;
}
