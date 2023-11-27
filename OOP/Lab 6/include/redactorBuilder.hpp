#ifndef REDACTOR_BUILDER_H_
#define REDACTOR_BUILDER_H_

#include <memory>

#include "LocationRedactor.hpp"
#include "battle/BattleManager.hpp"
#include "Serializer.hpp"
#include "Observer.hpp"

class RedactorTest;
class Builder {
public:
	std::shared_ptr<LocationRedactor> redactor;

	std::shared_ptr<ILocation> location;
	std::shared_ptr<LogObserver> observer;
	std::shared_ptr<BattleManager> battleManager;
	std::shared_ptr<LocationSerializer> serializer;
	std::shared_ptr<DangeonUndoManager> undoManager;
	bool allCompounentsSet = false;
public:
	friend RedactorTest;
	Builder();

	virtual std::shared_ptr<LocationRedactor> build();
	virtual Builder & setObserver(std::shared_ptr<LogObserver> _observer);
	virtual Builder & setLocation(std::shared_ptr<ILocation> _location);
	virtual Builder & setBattleManager(std::shared_ptr<BattleManager> _battleManager);
	virtual Builder & setSerializer(std::shared_ptr<LocationSerializer> _serializer);
	virtual Builder & setUndoManager(std::shared_ptr<DangeonUndoManager> _undoManager);
	virtual bool isAllCompounentsSet();
};

class RedactorDirector {
public:
	RedactorDirector() = default;
	std::shared_ptr<LocationRedactor> createDangeonRedactor(Builder & builder, std::shared_ptr<std::ofstream> logFile, bool createNewLocation = true);
};

#endif