#ifndef REDACTOR_BUILDER_H_
#define REDACTOR_BUILDER_H_

#include <memory>

#include "LocationRedactor.hpp"
#include "battle/BattleManager.hpp"
#include "Serializer.hpp"
#include "Observer.hpp"

class Builder {
public:
	std::shared_ptr<LocationRedactor> redactor;
public:
	Builder();

	virtual std::shared_ptr<LocationRedactor> build();
	virtual Builder & setObserver(std::shared_ptr<LogObserver> _observer);
	virtual Builder & setLocation(std::shared_ptr<ILocation> _location);
	virtual Builder & setBattleManager(std::shared_ptr<BattleManager> _battleManager);
	virtual Builder & setSerializer(std::shared_ptr<LocationSerializer> _serializer);
	virtual Builder & setUndoManager(std::shared_ptr<DangeonUndoManager> _undoManager);
};

class RedactorDirector {
private:
	std::string fileLogName = "LocationRedactor.log";
public:
	std::shared_ptr<LocationRedactor> createDangeonRedactor(Builder & builder);
};

#endif