#ifndef UNDO_MANAGER_H_
#define UNDO_MANAGER_H_

#include <string>
#include <stack>
#include <type_traits>
#include <memory>
#include <vector>

#include "Location.hpp"
#include "Observer.hpp"
#include "MobFabric.hpp"
#include "UndoVisitor.hpp"

enum class StateType {
	fullCopy,
	base,
	offset
};

class IState;
class IUndoManager {
public:
	virtual IUndoManager & addState(IState && state) = 0;
	virtual IState & undo() = 0;
};

class DangeonUndoManager : public IUndoManager {
private:
	std::stack<IState> states;
	std::shared_ptr<LogObserver> logObserver;
	std::shared_ptr<ILocation> location;
	UndoVisitor visitor;
public:
	DangeonUndoManager(std::shared_ptr<ILocation> _location, std::shared_ptr<LogObserver> _logObserver) :
		location(_location), logObserver(_logObserver), visitor(_location) {};
	IState & undo() override;
	IUndoManager & addState(IState && state) override;

	void onAdd(const MobData & mob);
	void onMove(const MobData & mob, Position to);
	void onAttack(const MobData & idAttacker, const MobData & idDefender);
};


class IState {
public:
	virtual std::string toString() = 0;
	virtual IState & fromString(std::string _data) = 0;
	virtual void accept(UndoVisitor & visitor) = 0;
};

class StateAdd;
class StateBase : public IState {
private:
	std::vector<StateAdd> mobAdds;
public:
	friend UndoVisitor;

	StateBase(std::vector<StateAdd> & _mobsAdds) : mobAdds(_mobsAdds) {}

	std::string toString() override;
	IState & fromString(std::string _data) override;

	void accept(UndoVisitor & visitor) override {
		visitor.visit(*this);
	}

};

class StateAdd : public IState {
private:
	std::shared_ptr<MobData> mobToAdd;
	StateAdd() = default;
public:
	friend UndoVisitor;
	friend StateBase;

	StateAdd(std::shared_ptr<MobData> _mobToAdd) : mobToAdd(_mobToAdd) {}

	std::string toString() override;
	IState & fromString(std::string _data) override;

	void accept(UndoVisitor & visitor) override {
		visitor.visit(*this);
	}
};

class StateMove : public IState {
private:
	std::shared_ptr<MobData> mobToMove;
	Position from;
	Position to;
public:
	friend UndoVisitor;

	StateMove(std::shared_ptr<MobData> _mobToMove, Position & _from, Position & _to)
		: mobToMove(_mobToMove)
		, from(_from)
		, to(_to) {}

	std::string toString() override;
	IState & fromString(std::string _data) override;

	void accept(UndoVisitor & visitor) override {
		visitor.visit(*this);
	}
};

class StateRemove : public IState {
private:
	std::shared_ptr<MobData> mobToRemove;
public:
	friend UndoVisitor;

	StateRemove(std::shared_ptr<MobData> _mobToRemove) : mobToRemove(_mobToRemove) {};

	std::string toString() override;
	IState & fromString(std::string _data) override;

	void accept(UndoVisitor & visitor) override {
		visitor.visit(*this);
	}
};

class UndoUpdateData : public IUpdateData {
private:
	IState & state;
public:
	UndoUpdateData(IState & _state) : state(_state) {}
	std::string asString() override {
		return state.toString();
	}
};

#endif // UNDO_MANAGER_H_