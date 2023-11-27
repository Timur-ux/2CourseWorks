#include "undoManager/UndoManager.hpp"
#include "undoManager/UndoVisitor.hpp"

std::string StateAdd::toString() {
	std::stringstream stateStream;

	stateStream << "action: add; Id: " << mobToAdd->getId();

	return stateStream.str();
}

void StateAdd::accept(UndoVisitor & visitor) {
	visitor.visit(*this);
}

std::string StateMove::toString() {
	std::stringstream stateStream;

	stateStream << "action: move; Id: " << mobToMove->getId();

	return stateStream.str();
}

void StateMove::accept(UndoVisitor & visitor) {
	visitor.visit(*this);
}

std::string StateRemove::toString() {
	std::stringstream stateStream;

	stateStream << "action: remove; Id: " << mobToRemove->getId();

	return stateStream.str();
}

void StateRemove::accept(UndoVisitor & visitor) {
	visitor.visit(*this);
}

std::string StateBase::toString() {
	std::stringstream stateStream;

	for (auto & state : mobAdds) {
		stateStream << state.toString() << " ; ";
	}

	return stateStream.str();
}

void StateBase::accept(UndoVisitor & visitor) {
	visitor.visit(*this);
}

IUndoManager & DangeonUndoManager::undo() {
	if (states.empty()) {
		return *this;
	}

	isNowUndoTime = true;

	std::shared_ptr<IState> state = states.top();
	states.pop();

	state->accept(visitor);
	logObserver->update(
		std::make_shared<UndoUpdateData>(*state, false)
	);

	isNowUndoTime = false;
	return *this;
}

IUndoManager & DangeonUndoManager::addState(std::shared_ptr<IState> state) {
	if (isNowUndoTime) {
		return *this;
	}

	states.push(state);

	return *this;
}

void DangeonUndoManager::onAdd(const MobData & mob) {
	std::shared_ptr<MobData> mobPtr{ new MobData(mob) };
	addState(
		std::make_shared<StateAdd>(mobPtr)
	);
}

void DangeonUndoManager::onMove(const MobData & mob, Position from, Position to) {
	addState(
		std::make_shared<StateMove>(
			std::make_shared<MobData>(mob),
			from,
			to
		)
	);
}

void DangeonUndoManager::onRemove(const MobData & mob) {
	addState(
		std::make_shared<StateRemove>(
			std::make_shared<MobData>(mob)
		)
	);
}

UndoUpdateData::UndoUpdateData(IState & _state, bool isSave) : state(_state) {
	if (isSave) {
		undoType = "Undo(Remember)";
	}
	else {
		undoType = "Undo(Return)";
	}
}

std::string UndoUpdateData::asString() {
	std::stringstream os;

	os << undoType << ": " << state.toString();

	return os.str();
}

void UndoVisitor::visit(StateAdd & state) {
	auto mobData = state.mobToAdd;

	std::shared_ptr<ILocation> _location = location.lock();
	if (_location) {
		_location->removeMob(mobData->getId());
	}
}

void UndoVisitor::visit(StateMove & state) {
	auto mobData = state.mobToMove;

	std::shared_ptr<ILocation> _location = location.lock();
	if (_location) {
		_location->moveMob(
			mobData->getId()
			, state.from
		);
	}
}

void UndoVisitor::visit(StateRemove & state) {
	auto mobData = state.mobToRemove;

	std::shared_ptr<ILocation> _location = location.lock();
	if (_location) {
		_location->addMob(*mobData);
	}
}

void UndoVisitor::visit(StateBase & state) {
	auto & statesAdd = state.mobAdds;

	for (auto & stateAdd : statesAdd) {
		visit(stateAdd);
	}
}

ILocation & DangeonLocation::addMob(MobData _mobData) {
	auto pos = _mobData.getPosition();
	if (pos.getX() > width or pos.getX() < 0) {
		throw std::invalid_argument(
		"position on X out of range. Max: "
		+ std::to_string(width)
		+ ". Min: 0. Given: "
		+ std::to_string(pos.getX()));
	}
	if (pos.getY() > height or pos.getY() < 0) {
		throw std::invalid_argument(
		"position on Y out of range. Max: "
		+ std::to_string(height)
		+ ". Min: 0. Given: "
		+ std::to_string(pos.getY()));
	}
	if (_mobData.id < 0 or mobs.find(_mobData.id) != std::end(mobs)) {
		_mobData.id = mobs.size();
	}
	mobs[_mobData.id] = _mobData;

	logObserver->onAdd(_mobData);
	undoManager->onAdd(_mobData);

	return *this;
}

ILocation & DangeonLocation::moveMob(int id, Position newPos) {
	if (mobs.find(id) == std::end(mobs)) {
		throw std::invalid_argument("Location hasn't mob with id: " + std::to_string(id));
	}

	MobData & data = mobs[id];

	Position oldPos = data.getPosition();
	data.position = newPos;

	logObserver->onMove(data, oldPos, newPos);
	undoManager->onMove(data, oldPos, newPos);

	return *this;
}

ILocation & DangeonLocation::removeMob(int id) {
	auto mobIterator = mobs.find(id);
	if (mobIterator == std::end(mobs)) {
		throw std::invalid_argument("Location hasn't mob with id: " + std::to_string(id));
	}

	logObserver->onRemove(mobIterator->second);
	undoManager->onRemove(mobIterator->second);
	mobs.erase(mobIterator);

	return *this;
}