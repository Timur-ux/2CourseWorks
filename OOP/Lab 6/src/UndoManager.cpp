#include "UndoManager.hpp"
#include "UndoVisitor.hpp"

std::string StateAdd::toString() {
	std::stringstream stateStream;

	stateStream << "add "
		<< mobToAdd->getId()
		<< " " << MobTypeCvt::to_string(mobToAdd->getMobType())
		<< " " << mobToAdd->getMob()->getName()
		<< " " << mobToAdd->getPosition();

	return stateStream.str();
}

IState & StateAdd::fromString(std::string _data) {
	std::stringstream stateStream(_data);

	std::shared_ptr<Mob> mob;
	std::string action, strMobType, name;
	Position pos;
	int id;

	stateStream >> action >> id >> strMobType >> name >> pos;

	enumMobType type = MobTypeCvt::to_enum(strMobType);
	mob = MobFabric::create(type);

	mobToAdd = std::make_shared<MobData>(mob, pos, type, id);

	return *this;
}

void StateAdd::accept(UndoVisitor & visitor) {
	visitor.visit(*this);
}

std::string StateMove::toString() {
	std::stringstream stateStream;

	stateStream << "move "
		<< mobToMove->getId()
		<< " " << MobTypeCvt::to_string(mobToMove->getMobType())
		<< " " << mobToMove->getMob()->getName()
		<< " " << from
		<< " " << to;

	return stateStream.str();
}

IState & StateMove::fromString(std::string _data) {
	std::stringstream stateStream(_data);

	std::shared_ptr<Mob> mob;
	std::string action, strMobType, name;
	Position _from, _to;
	int id;

	stateStream >> action >> id >> strMobType >> name >> _from >> _to;

	enumMobType type = MobTypeCvt::to_enum(strMobType);
	mob = MobFabric::create(type);
	from = _from;
	to = _to;
	mobToMove = std::make_shared<MobData>(mob, to, type, id);

	return *this;
}

void StateMove::accept(UndoVisitor & visitor) {
	visitor.visit(*this);
}

std::string StateRemove::toString() {
	std::stringstream stateStream;

	stateStream << "remove "
		<< mobToRemove->getId()
		<< " " << MobTypeCvt::to_string(mobToRemove->getMobType())
		<< " " << mobToRemove->getMob()->getName()
		<< " " << mobToRemove->getPosition();

	return stateStream.str();
}

IState & StateRemove::fromString(std::string _data) {
	std::stringstream stateStream(_data);

	std::shared_ptr<Mob> mob;
	std::string action, strMobType, name;
	Position pos;
	int id;

	stateStream >> action >> id >> strMobType >> name >> pos;

	enumMobType type = MobTypeCvt::to_enum(strMobType);
	mob = MobFabric::create(type);

	mobToRemove = std::make_shared<MobData>(mob, pos, type, id);

	return *this;
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

IState & StateBase::fromString(std::string _data) {
	mobAdds.erase(std::begin(mobAdds), std::end(mobAdds));
	std::stringstream streamData(_data);
	std::string delimeter;
	std::string mobAddData;

	StateAdd state;

	while (streamData >> mobAddData >> delimeter) {
		state.fromString(mobAddData);

		if (delimeter != ";") {
			break;
		}

		mobAdds.push_back(state);
	}

	return *this;
}

void StateBase::accept(UndoVisitor & visitor) {
	visitor.visit(*this);
}

IUndoManager & DangeonUndoManager::undo() {
	IState & state = states.top();

	state.accept(visitor);
	logObserver->update(
		std::make_shared<UndoUpdateData>(state, false)
	);
	states.pop();

	return *this;
}

IUndoManager & DangeonUndoManager::addState(IState && state) {
	states.push(state);

	logObserver->update(
		std::make_shared<UndoUpdateData>(state)
	);

	return *this;
}

void DangeonUndoManager::onAdd(const MobData & mob) {
	addState(
		StateAdd(
			std::make_shared<MobData>(mob)
		)
	);
}

void DangeonUndoManager::onMove(const MobData & mob, Position from, Position to) {
	addState(
		StateMove(
			std::make_shared<MobData>(mob),
			from,
			to
		)
	);
}

void DangeonUndoManager::onRemove(const MobData & mob) {
	addState(
		StateRemove(
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

	location->removeMob(mobData->getId());
}

void UndoVisitor::visit(StateMove & state) {
	auto mobData = state.mobToMove;

	location->moveMob(
		mobData->getId()
		, state.from
	);
}

void UndoVisitor::visit(StateRemove & state) {
	auto mobData = state.mobToRemove;

	location->addMob(*mobData);
}

void UndoVisitor::visit(StateBase & state) {
	auto & statesAdd = state.mobAdds;

	for (auto & stateAdd : statesAdd) {
		visit(stateAdd);
	}
}
